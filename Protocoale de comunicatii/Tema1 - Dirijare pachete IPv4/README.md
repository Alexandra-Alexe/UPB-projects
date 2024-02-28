#TEMA1 PROTOCOALE DE COMUNCATIE

-> Am realizat doar partea de dirijare din cadrul acestei teme, dar trebuie sa mentionez
ca m-am chinuit ceva timp pentru ca eu testam tema desi nu o facusem complet si am 
avut constant senzatia ca gresesc la partea de checksum.

-> Am urmat pasii din cerinta pentru protocolul IPv4, asa cum am marcat si in cod:
    - am verificat ca pachetul sa nu fie malformat, punand conditia unei dimensiuni
minime
    - verificand campul Ether Type, se prelucreaza ulterior doar antetele IPv4 si ARP
    - se verifica daca destinatia finala este ruterul in cauza, caz in care pachetul
nu se trimite mai departe. Folosesc functia inet_addr pentru a converti stringul 
ip_addr intr-o reprezentare numerica in retea.
    - se recalculeaza suma de control a pachetului, iar daca difera de cea existenta 
in structura pachetul se arunca, fiind corupt
    - in cazul in care campul time to live are valoarea mai mica ca 1, pachetul se 
arunca si campul este decrementat
    - cu ajutorul unei functii auxiliare, get_best_route, se cauta in tabela de rutare
adresa ip cea mai potrivita pentru ca pachetul sa ajunga la destinatie. Functia 
itereaza prin tabela de rutare, realizeaza un & pe biti intre masca de retea, adresa 
IP destinatie si prefixele date. Se returneaza intrarea in tabela care are cea mai
lunga masca de retea sau NULL la insucces.
    - se actualizeaza suma de control in antetul IP al pachetului
    - cu ajutorul functiei auxiliare get_mac_entry, se itereaza prin mac table 
cautandu-se adresa MAC a adresei IP gasite prin functia get_best_route. Se returneaza
intrarea in mac table sau NULL la insucces.
    - pentru a pregati cadrul, la adresa sursa se suprascrie adresa mac a interfetei
gasite prin functia get_best_route, iar la adresa destinatie se suprascrie adresa
mac a intrarii gasite in mac table. 
    - pachetul este trimis mai departe prin functia send_to_link