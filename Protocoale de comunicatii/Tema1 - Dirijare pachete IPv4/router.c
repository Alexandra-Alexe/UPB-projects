#include "queue.h"
#include "lib.h"
#include "protocols.h"
#include <string.h>
#include <arpa/inet.h>

struct route_table_entry *rtable;
int len_rtable;

struct arp_entry *arp_table;
int len_arp_table ;

/*functie care itereaza prin tabela MAC si returneaza o intrare care sa 
	se potriveasca cu adresa ip*/
struct arp_entry *get_mac_entry(uint32_t dest_ip) {
	for (int i = 0; i < len_arp_table; i++) {
        	if (arp_table[i].ip == dest_ip)
            	return &arp_table[i];
    }
	return NULL;
}
 /*functie care itereaza prin tabela de rutare si returneaza o intrare
 	care corespune in cea mai mare masura unui prefix*/
struct route_table_entry *get_best_route(uint32_t ip_dest) {
	struct route_table_entry *aux = NULL;
	for(int i = 0; i < len_rtable; i++) {
		if(( ip_dest & rtable[i].mask) == (rtable[i].mask & rtable[i].prefix) ) {
			if(aux == NULL || (ntohl(rtable[i].mask) > ntohl(aux->mask)) ) {
				aux = &rtable[i];
			}
		}
	}
	return aux;
}


int main(int argc, char *argv[])
{
	setvbuf(stdout, NULL, _IONBF, 0);
	char buf[MAX_PACKET_LEN];

	// Do not modify this line
	init(argc - 2, argv + 2);

	// Tabela de rutare
	rtable = malloc(sizeof(struct route_table_entry) * 80000);
	DIE(rtable == NULL, "memory rtable");
	len_rtable = read_rtable(argv[1], rtable); 

	// Tabela MAC
	arp_table = malloc(sizeof(struct arp_entry) * 80000);
	DIE(arp_table == NULL, "memory arp_table");
	len_arp_table = parse_arp_table("arp_table.txt", arp_table);


	while (1) {

		int interface;
		size_t len;

		interface = recv_from_any_link(buf, &len);
		DIE(interface < 0, "recv_from_any_links");

		struct ether_header *eth_hdr = (struct ether_header *) buf;
		/* Note that packets received are in network order,
		any header field which has more than 1 byte will need to be conerted to
		host order. For example, ntohs(eth_hdr->ether_type). The oposite is needed when
		sending a packet on the link, */

		// parsarea pachetului
		if(sizeof(*eth_hdr) < 4*sizeof(uint8_t)) {  
			printf("Corrupted packet\n");
			continue;
		} 

		if((ntohs(eth_hdr->ether_type) == 0x0800) || (ntohs(eth_hdr->ether_type) == 0x0806)) {
			struct iphdr *ip_hdr = (struct iphdr *)(buf + sizeof(struct ether_header));
			
			//se verifica daca routerul este destinatia
			char * ip_addr = get_interface_ip(interface); 
			uint32_t ip_addr_num = inet_addr(ip_addr); 
			if(ntohs(ip_hdr->daddr) == ip_addr_num) { 
				printf("This router is the destination\n");
				continue;
			}

			//verificare checksum
			uint16_t old_check = ip_hdr->check;
			ip_hdr->check = 0;
			uint16_t new_check = htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr)));
			if (new_check !=  old_check) {
				printf("Corrupted packet\n");
				continue;
			}

			//verificare si actualizare ttl
			if(ip_hdr->ttl <= 1) {
				printf("Time exceeded\n");
				continue;
			}
			ip_hdr->ttl --;

			//cautare in tabela de rutare
			struct route_table_entry *best_route = get_best_route(ip_hdr->daddr);
			if(best_route == NULL) {
				printf("Destination unreachable\n");
				continue;
			}

			//actualizare checksum
			ip_hdr->check = 0;
			ip_hdr->check = htons(checksum((uint16_t *)ip_hdr, sizeof(struct iphdr)));
			
			//cautare in mac table 
			struct arp_entry *next_hop_mac = get_mac_entry(best_route->next_hop);
			if(next_hop_mac == NULL) {
				printf("nu s-a gasit adresa mac\n");
				continue;
			}

			//rescriere adrese L2
			memcpy(eth_hdr->ether_dhost, next_hop_mac->mac,sizeof(eth_hdr->ether_dhost));
			get_interface_mac(best_route->interface, eth_hdr->ether_shost);

			//trimiterea noului pachet
			int aux = send_to_link(best_route->interface, buf, len);
			DIE(aux < 0, "send_to_link");
		
		}
	}
	free(rtable);
	free(arp_table);
}