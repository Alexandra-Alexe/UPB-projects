#!/usr/bin/env python3

import base64
import binascii
from encodings import utf_8
import json
import gmpy2
from random import randint
import os

def str_to_number(text):
    """ Encodes a text to a long number representation (big endian). """
    return int.from_bytes(text.encode("latin1"), 'big')

def number_to_str(num):
    """ Decodes a text to a long number representation (big endian). """
    num = int(num)
    return num.to_bytes((num.bit_length() + 7) // 8, byteorder='big').decode('latin1')

def encrypt(pub_k, msg_num):
    """ We only managed to steal this function... """
    cipher_num = gmpy2.powmod(msg_num, pub_k["e"], pub_k["n"])
    # note: gmpy's to_binary uses a custom format (little endian + special GMPY header)!
    cipher_b64 = base64.b64encode(gmpy2.to_binary(cipher_num))
    return cipher_b64

def decrypt(priv_k, cipher):
    """ We don't have the privary key, anyway :( """
    # you'll never get it!
    pass


if __name__ == "__main__":

    msg = "eyJuIjogMTcyMjc1NDI3NDQ0Mzk2Mzk2NDg5Nzg0MTQ2OTA1MjkyMTkxNzkzMzU5NzU0MTQ2ODc2NDI2NTA2MjE0NjY4NTAyMjExODk3NTY0NjM4ODE3MDg1MTg3OTE1NTQxNzQ1MTY2MDM4MzAzNzM5NDk5OTM3Nzg2NjgzOTc0MDExNDg3Nzc5NDc0NDAxNTI5MjQyNDkxODkyNjQ1OTY4OTU5MTExNjU2MTAxNTc2NTM4NTc4NDc5NDg0MDQxODczMzQ3MTQ4MDExMzk1Njk0OTI0NTQ5NDgwMTk4ODYzMjM5OTcyNDc2NjY1ODU1MzYyMTMzOTMxMjI0MjQwODQ2NTEwNzcyNzIwNTk4MjgwNjMzMzYwMjgzNzc0OTkyNDYzMDM2OTI0OTkwOTc1NTU3NDcyODU4NDEzMzc1MDQ2NTc2MzY4NDQwNzQxMDY3NjMyOTA4MzAzNTY1ODkzMzk2NzIwOTk5NzY3OTk5NTc1MDA2MjcxOTY2ODM4ODc2MDg2MTAwNzA4ODA1Njk5NTE2ODQ3NDQ1NjgxMDM2NzQxMTkxNjQyMjE4MjQwNDU3MDcwMDc5NTgwNDA4Njc0OTMyMDY4NzI1ODc2NDIxNjU5ODA0NjM4OTQxODc0MjQzMTQwNDcwNjM0ODEyNDY0NzQ0MzYzODcwODgwMjUwMzUwNjgzNDIzMTk4NTM4ODUwNTc2NDUzMDQ0MDk4NTMwOTkzNDg3OTE0MTE0MTU1Mzc2NTgxNDM1Mjg3ODc2MzUzMzE1NjAzODI5NDY1MDg4MjY5ODAwMTQ2Mjc0NTIwOTk1OTMyNzI5Nzk1NDcyNDcsICJlIjogMTA5MjM3LCAiZmxhZyI6ICJBUUUvaVAvRllxRHh3Rk1rUitZdjZoVnVzSHp3T05mOTIvSE1ERlVNb1JxdnBsdHlOSjJpaXh2cUlMbG1WNmRXWXRDMGxZTEo2Um92TFZKcjVSWERtQzVhQTVlWDNKczY1anV1U0MxSjhPTTFzTFN2R0pseDl5MGk0SHpDSHpBaU42MDBRdjBkbFVQL25yam1tOVBMdEZZZVJjR0g3akhJb1h4M2xXQ0M1ZUVsNzArNGgwUG9hUGo3elJTNEdlVXNjc3lwQVJ3T2xqUVRPTjlNTXRXZXZyaHlZb09NUFlkUUx0YXFZVGtPRmlRazVvYkkyZ3B1OUhzTGlrdXlhZnRrQWNvd0ZnejJEQUc1aHFHS0wyenFKeURJTlRqSFVpb2xVMi9IbWNienFKOFplc0wrRjdLK01DaEVPQXVjN3RnLzdEM094U1JPb3lhNG5uWjBaZCtBY1Y4PSJ9"
    

    x = json.loads(base64.b64decode(msg))
    print("mesajul meu decodif b64")
    print(x)

    random = 3
    cypher_dash = (gmpy2.from_binary(base64.b64decode(x['flag'])) * (gmpy2.powmod(random ,x['e'], x['n']))) % x['n']
    
    json_msg = {
        "n": 17227542744439639648978414690529219179335975414687642650621466850221189756463881708518791554174516603830373949993778668397401148777947440152924249189264596895911165610157653857847948404187334714801139569492454948019886323997247666585536213393122424084651077272059828063336028377499246303692499097555747285841337504657636844074106763290830356589339672099976799957500627196683887608610070880569951684744568103674119164221824045707007958040867493206872587642165980463894187424314047063481246474436387088025035068342319853885057645304409853099348791411415537658143528787635331560382946508826980014627452099593272979547247,
        "e": 109237,
        "flag": base64.b64encode(gmpy2.to_binary(cypher_dash)).decode('utf-8')}

    
    for_server_msg = base64.b64encode(json.dumps(json_msg).encode())
    print("mesajul de trimis la server")
    print(for_server_msg)
    print()

    d_uni = b'\xfaQ0<Z8\xd3E$6r$0\x0fD\xeb\x00\x00\x0b\xc4\th\xc9\xf3\xf4)\xd5\xa0H8\xfaTKi*M\xa2\x90\xe7\xca,\xff\xcaw'
    d_dec = d_uni.decode("unicode_escape")
    d = str_to_number(d_dec)
    res = d // random
    
    print(number_to_str(res))
    
