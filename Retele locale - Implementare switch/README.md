
#   TEMA 1 - RL

Am rezolvat cerintele 1 si 2.

TASK 1 - Procesul de comutare:
 - Pornind de la pseudocodul dat, am realizat procesul de comutare. 
 Am declarat dictionarul MAC_Table, folosit pentru a retine perechile
de adresa MAC si interfata corespunzatoare. Cu fiecare pachet ce 
ajunge la switch, in tabela MAC se mai adauga o intrare, daca nu 
exista deja; mai exact adresa MAC sursa a cadrului. Apoi, daca se 
face unicast si daca adresa destinatie exista in tabela, se apeleaza
functia forward_frame pentru a trimite pachetul direct la destinatie.
Daca insa, adresa destinatie nu este gasita in tabela, se va face 
flood, pachetul fiind trimis pe toate interfetele mai putin cea de 
pe care a venit. Iar in caz de multicast, se trimite pachetul in mod
asemanator pe toate interfetele, mai putin pe cea de unde a venit. 
 - Functia forward_frame, apeleaza functia send_to_link pentru a trimite 
 cadrul, avand ca parametrii interfata, datele si lungimea lor.
 - Functia is_unicast determina daca adresa mac este o adresa unicast sau
  nu prin verificarea primului bit al primului octet.

 TASK 2 - Functionalitatea de VLAN:
  - Pentru citirea datelor din fisierele de configurare, am creat functia
read_switch_config. Se deschide fisierul, cu ajutorul variabilei lines,
 se citeste fiecare linie si se retin prioritatea switchului, interfata si
vlan id-ul cu care se populeaza VLAN_Table-ul. In cazul interfetelor trunk,
 in VLAN_Table se marcheaza cu -1. Ulterior, am modificat gestionarea 
cadrului pentru fiecare dintre cele 3 cazuri: adresa mac destinatie 
existenta, unicast cu adresa mac dest negasita si multicast. De fiecare data
se stabileste tipul legaturii de pe care vine cadrul, apoi tipul legaturii pe
 care pleaca. Cele 4 cazuri sunt:
    -- trunk -> trunk : caz in care pachetul este trimis mai departe exact asa
cum a venit, cu tag.
    -- trunk -> access : caz in care cadrul se trimite mai departe numai daca 
vlan-ul interfetei ce urmeaza este egal cu vlan-ul inclus in tag.
    -- access -> trunk : caz in care cadrului i se adauga tag inainte de a fi 
trimis
    -- access -> access : caz in care se verifica egalitatea vlan id-urilor de
pe interfetele de intrare si iesire, si la egalitate cadrul este trimis mai 
departe fara modificari
 - Mi-am definit functia forward_frame_add_tag prin care adaug vlan id-ul dat ca
parametru in cadrul cu date si trimit pachetul cu send_to_link.
 - Tot intr-o functie separata, forward_frame_without_tag, scot cei 4 bytes ai 
tag-ului din cadru si il trimit mai departe. 
