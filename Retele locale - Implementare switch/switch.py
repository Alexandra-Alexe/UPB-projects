#!/usr/bin/python3
import sys
import struct
import wrapper
import threading
import time
from wrapper import recv_from_any_link, send_to_link, get_switch_mac, get_interface_name

# variabile globale
MAC_Table = {}
VLAN_Table = {}

def parse_ethernet_header(data):
    # Unpack the header fields from the byte array
    #dest_mac, src_mac, ethertype = struct.unpack('!6s6sH', data[:14])
    dest_mac = data[0:6]
    src_mac = data[6:12]
    
    # Extract ethertype. Under 802.1Q, this may be the bytes from the VLAN TAG
    ether_type = (data[12] << 8) + data[13]

    vlan_id = -1
    # Check for VLAN tag (0x8100 in network byte order is b'\x81\x00')
    if ether_type == 0x8200:
        vlan_tci = int.from_bytes(data[14:16], byteorder='big')
        vlan_id = vlan_tci & 0x0FFF  # extract the 12-bit VLAN ID
        ether_type = (data[16] << 8) + data[17]

    return dest_mac, src_mac, ether_type, vlan_id


def create_vlan_tag(vlan_id):
    # 0x8100 for the Ethertype for 802.1Q
    # vlan_id & 0x0FFF ensures that only the last 12 bits are used
    return struct.pack('!H', 0x8200) + struct.pack('!H', vlan_id & 0x0FFF)

def send_bdpu_every_sec():
    while True:
        # TODO Send BDPU every second if necessary
        time.sleep(1)
        

def forward_frame(data, output_interface):
    # apelul către send_to_link pentru a trimite cadrul pe interfața specificată
    send_to_link(output_interface, data, len(data))

def is_unicast(mac_address):
    # convertesc adresa MAC într-un șir de octeți hexa
    mac_bytes = mac_address.split(':')

    # verific primul bit al primului octet
    return int(mac_bytes[0], 16) % 2 == 0


def forward_frame_add_tag(data, output_interface, vlan_id):

    data = data[0:12] + create_vlan_tag(vlan_id) + data[12:]
    send_to_link(output_interface, data, len(data))
    

def forward_frame_without_tag(data, output_interface):

    data_without_tag = data[0:12] + data[16:]
    send_to_link(output_interface, data_without_tag, len(data_without_tag))
        


def read_switch_config(switch_id):
    config_file = f'configs/switch{switch_id}.cfg'

    with open(config_file, 'r') as file:
        lines = file.readlines()

    switch_priority = None
    i = 0  

    for line in lines:
        tokens = line.strip().split()

        if tokens:
            if tokens[0].isdigit():
                switch_priority = int(tokens[0])
            else:
                interface = tokens[0]

                if len(tokens) > 1 and tokens[1] == 'T':
                    VLAN_Table[i] = -1  
                elif len(tokens) > 1 and tokens[1].isdigit():
                    VLAN_Table[i] = int(tokens[1])  

                i += 1  

            

def main():
    # init returns the max interface number. Our interfaces
    # are 0, 1, 2, ..., init_ret value + 1
    switch_id = sys.argv[1]

    num_interfaces = wrapper.init(sys.argv[2:])
    interfaces = range(0, num_interfaces)

    print("# Starting switch with id {}".format(switch_id), flush=True)
    print("[INFO] Switch MAC", ':'.join(f'{b:02x}' for b in get_switch_mac()))

    # Create and start a new thread that deals with sending BDPU
    t = threading.Thread(target=send_bdpu_every_sec)
    t.start()

    # Printing interface names
    for i in interfaces:
        print(get_interface_name(i))

    
    read_switch_config(switch_id)

    while True:
        

        # Note that data is of type bytes([...]).
        # b1 = bytes([72, 101, 108, 108, 111])  # "Hello"
        # b2 = bytes([32, 87, 111, 114, 108, 100])  # " World"
        # b3 = b1[0:2] + b[3:4].
        interface, data, length = recv_from_any_link()

        dest_mac, src_mac, ethertype, vlan_id = parse_ethernet_header(data)

        # Print the MAC src and MAC dst in human readable format
        dest_mac = ':'.join(f'{b:02x}' for b in dest_mac)
        src_mac = ':'.join(f'{b:02x}' for b in src_mac)

        # Note. Adding a VLAN tag can be as easy as
        # tagged_frame = data[0:12] + create_vlan_tag(10) + data[12:]

        print(f'Destination MAC: {dest_mac}')
        print(f'Source MAC: {src_mac}')
        print(f'EtherType: {ethertype}')

        print("Received frame of size {} on interface {}".format(length, interface), flush=True)

        # TODO: Implement forwarding with learning
        src = src_mac
        dst = dest_mac

        if src not in MAC_Table:
            MAC_Table[src] = interface


        if is_unicast(dst):
            if dst in MAC_Table:

                if VLAN_Table[interface] == -1:
                    # trunk - trunk
                    if VLAN_Table[MAC_Table[dst]] == -1:
                        forward_frame(data, MAC_Table[dst])

                    #trunk - access
                    elif VLAN_Table[MAC_Table[dst]] == vlan_id: 
                        forward_frame_without_tag(data, MAC_Table[dst])

                elif VLAN_Table[interface] != -1:

                    #acces - trunk
                    if VLAN_Table[MAC_Table[dst]] == -1:
                        forward_frame_add_tag(data, MAC_Table[dst], VLAN_Table[interface])

                    #acees - acces
                    elif VLAN_Table[interface] == VLAN_Table[MAC_Table[dst]]:
                        forward_frame(data, MAC_Table[dst])
            else:
                for o in interfaces:
                    if o != interface:
                        
                        if VLAN_Table[interface] == -1:
                            if VLAN_Table[o] == -1:
                                forward_frame(data, o)
                            elif  VLAN_Table[o] == vlan_id:
                                forward_frame_without_tag(data, o)
                        elif VLAN_Table[interface] != -1:
                            if VLAN_Table[o] == -1:
                                forward_frame_add_tag(data, o, VLAN_Table[interface])
                            elif VLAN_Table[interface] == VLAN_Table[o]:
                                forward_frame(data, o)
        else:
            for o in interfaces:
                if o != interface:
                    
                    if VLAN_Table[interface] == -1:
                        if VLAN_Table[o] == -1:
                            forward_frame(data, o)
                        elif VLAN_Table[o] == vlan_id:
                            forward_frame_without_tag(data, o)
                    elif VLAN_Table[interface] != -1:
                        if VLAN_Table[o] == -1:
                            forward_frame_add_tag(data, o, VLAN_Table[interface])
                        elif VLAN_Table[interface] == VLAN_Table[o]:
                            forward_frame(data, o)



        # TODO: Implement VLAN support       
        # TODO: Implement STP support


        # data is of type bytes.
        # send_to_link(i, data, length)

if __name__ == "__main__":
    main()
