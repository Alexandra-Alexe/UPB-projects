TEMA 1  -  ISC 

Task1  - Crypto attack


Task-ul asta l-am inceput cand mi-am dat seama cum sa decodez hint ul din cerinta:
cu cifrul caesar. Apoi a urmat partea in care am facut research despre rsa chosen attack.
Codificarea din message.txt am spart-o cu base64 si am ajuns la json ul cu e, n si flag ul.
Conform algoritmului, am scos chiper dash ul din flag. Si dupa trebuia sa trimit datele 
impachetate cumva la server deci am incercat tot cu json, asa cum le-am si primit, si 
codificate in acelasi mod cu base64. Dupa ce am trimis mesajul, am primit inapoi un sir de 
bytes, care a trebuit curatat cu decode unicode. Ca sa impart prin numarul random, a fost necesar
sa prelucrez mai departe sirul ca sir format doar din numere. La final pentru a afisa flag-ul l-am readus in string si l-am afisat. Fisierul python de care m-am folosit se numeste crypto.py si
este adaugat in aceasta arhiva. Flag ul gasit: SpeishFlag{aeZlNUUYAXxCQQcG5mhSqnxco60MCdUC}

### Task2 - Linux ACL

Dupa ce am cautat in mai multe directoare, am gasit fisierele din /usr/local/bin, dintre
care, robot-sudo este creat de wallybot, din grupul bossel. De aici am dedus ca va fi necesar 
sa pot rula drept wallybot. Am incercat sa rulez toate fisierele si sa imi dau seama cum 
functioneaza. Continutul lui vacuum-control a fost de asemenea interesant, m-am intors la 
el putin mai tarziu.

Abia atunci cand am rulat strings pe robot-sudo, am ajuns printre altele la urmatorul indiciu,
fiserul de configurare /etc/udev/whatsthis.conf/r0b0t3rs.conf. Afisand continutul lui, am dedus ca
 junitor poate rula orice script cu prefixul /usr/local/bin/vacuum-control. Deci pentru a deveni
  wallybot, prin robot-sudo trebuie sa ma folosesc de acel prefix. Am analizat mai departe
/var/lib/initscripts/hi/b05s.exe (gasit tot in fisierul r0b0t3rs.conf) cu strings pentru a vedea 
cum trebuie sa continui. Asa am ajuns la mesajul:
            "af063dbb2fc2eecd20875b3761f1d888
            Access denied!
            I will contact you when I require your cleaning services, janitor!
            Congratulations, here's your flag:
            cat /var/local/trap/manele/.zaflag". 
    
Nu am permisiuni sa pt a vedea continutul lui .xaflag. In mesaj se mai gasea ceva ce parea o cheie
de acces. Nu m-a ajutat sa deschid fisierul cu flag-ul, din pacate :( . Dupa mai multe incercari, m-am
prin ca cheia ajuta in combinatie cu fisierul anterior, b05s.exe, generand un output care se regaseste 
in mesaj, cel cu "I will contact you when I require your cleaning services, janitor!". 
    
M-am intors la fisierul vacuum-control, unde am adaugat "/var/lib/initscripts/hi/b05s.exe
 af063dbb2fc2eecd20875b3761f1d888", adica fisierul care poate fi rulat de wallybot si cheia de acces.
Mi-am dat seama ca nu pot modifica direct vacuum-control asa ca a trebuit sa copiez fisierul, in altul
creat de mine. La final l-am rulat cu robot-sudo si cu /var/lib/initscripts/hi/b05s.exe, fiserul lui wallybot, si cu cheia de accesaf063dbb2fc2eecd20875b3761f1d888. Asa am obtinut flag-ul :
SpeishFlag{hkhxsz9I2S7e5FcdgcZvEu5qad76oIVI}.


### Task3 - Binary Exploit

In primul rand, lipsind codul sursa, am analizat fisierul casino cu ghidra (nu mi-era dor de ghidra). Am
descoprit functia win care nu se apleaza nicaieri, si care mai mult ca sigur furnizeaza flag-ul meu. Deci trebuia
sa suprascriu adresa de retur a unei functii. Analizand codul din main si din functia loop, am gasit punctul de 
slabiciune al codului, adica scanf-ul prin care se citea sirul de numere. Deci trebuia sa suprascriu adresa de 
retur a functiei loop. Cu objdump, am cautat apelul acelui scanf, am gasit valoarea hexa care ar trebui sa imi
indice numerul de caractere de umplutura pe care ar trebui sa le dau. Nu era chiar acela numarul, dar am adaugat 4
si am ajuns la numarul meu. Practic daca il depaseam, primeam segmentation fault.La rezolvare am ajuns din aproape 
in aproape, prima data bucurandu-ma cand am primit un print din functia win, semn ca am ajuns unde trebuie. Adresa 
functiei win, tot cu objdump am obtinut-o si am avut grija sa o transform in decimal (dupa 12432 incercari cu ea
in hexa). 

Deci, dupa ce m-am conectat la server, mi-am introdus numele, am introdus initial niste numere random urmate de
x, asta pentru a se genera un lucky number si pentru a mi-l afisa. Dupa care i-am zis ca vreau sa continui, pentru 
ca de data asta sa introduc *comanda* . Asadar, comanda mea e formata din 39 de biti de umplutura, adresa functiei
win in decimal, un alt bit random pt a suprscrie adresa de retur a lui win, lucky number ul si x in final. Ulterior
i-am zis ca nu vreau sa continui pentru ca altfel mi-ar fi generat alt lucky number. Server-ul si-a luat la revedere
si mi-a afisat flag-ul : SpeishFlag{RQWlAHgi9xX2M1uCk8QtWflB3ujtFW62}