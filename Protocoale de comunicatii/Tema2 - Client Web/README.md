TEMA 2 - PCOM

    Am implementat tema 4 in limbajul C, fara a utiliza o biblioteca
de parsare deoarece eram obisnuita cu implementarea functiilor de 
modificare a stringurilor, folosind strchr si pointeri. Desi a fost
o tema mult mai usoara ca celelalte, am lucrat destul de mult pentru
ca am incercat sa realizez o implementare cat mai completa. Cel mai
mult timp am pierdut incercand sa imi dau seama de formatul pe care 
trebuie sa il aiba cererile. Trebuie sa mai mentionez ca am inceput 
implementarea de la codul laboratorului cu protocolul http.

    Am realizat o functie separata, extract_books, pe care o apelez
pentru a afisa continutul json ului, eliminand \n si parantezele. 
Folosind strchr, identific dupa parantez { }, inceputul datelor si
sfarsitul datelor pe care le afisez prin char *p. Cat timp mai exista 
o paranteza deschisa, se afiseaza date in continuare, existand un rand
liber intre carti diferite.

    In functia main exista instructiunea while prin care se citesc
comenzi pana la intalnirea comenzii exit prin care se iese din bucla
si se incheie programul. Citirea se face folosind fgets, iar ulterior
se foloseste strcspn pentru a identifica lungimea stringului citit, cu
scopul de a pun \0 pe pozitia potrivita.
    REGISTER: Voi descrie mai detaliat prima comanda register iar pe 
celelalte mai succint, accentuand diferentele dintre ele. La inceputul 
fiecarei comenzi se deschide conexiunea folosind open_connection, iar la 
final se inchide prin close_connection. Pentru comanda register se 
citeste username ul si parola astfel incat sa nu fie acceptate sirul vid
sau spatiile. Citirile datelor introduse de utilizator se fac in variabila 
input si se plaseaza ulterior in variabile specifice, a caror memorie este
eliberata la finalul acelei comenzi. Dupa, in variabila data, pun
informatiile dupa modelul unui json. Utilizez functia
compute_post_request, rezolvata in cadrul laboratorului pentru a creea
cererea, nu inainte de a pune variabila data intr un char**, conform
antetului functiei. Primesc raspunsul, cu ajutorul functiei 
receive_from_server si fac verificari asupra lui. Verific raspunsul
primit in response pentru a afisa mesajul corespunzator userului. In 
cazul comenzii register, scenariile posibile sunt fie de a inregistra
cu succes datele, fie ca acel username sa fie deja utilizat.

    LOGIN: Dupa deschiderea conexiunii si citirea datelor in variabilele
username si password, se construiesc datele in variabila data, in mod
asemanator, evident fiind diferit url-ul dat ca parametru functiei 
compute_post_request. Prin send_to_server, ajung informatiile la server
si prin receive_from_server, raspunsul se retine in variabila response.
Cazurile verificate sunt: daca parola introdusa este gresita, caz in care
user ul primeste mesajul "Parola incorecta!", daca contul nu a fost
inregistrat, caz in care se afiseaza "Nu exista cont pentru acest username!"
si cazul in care logarea se efectuat cu succes, afisandu-se "200 -OK - Bun 
venit!". Pe acest caz, folosind strstr se cauta in response inceputul
cookie-ului si finalul marcat de ; si se retine cookie-ul in variabila
realocata session_cookie, pentru a fi utilizata ulterior. Un caz alternativ
al comenzii login este cel in care se incearca logarea dar session_cookie
retine deja un string, deci clientul va primi mesajul "Esti deja logat!".

    ENTER_LIBRARY: In cazul acestei comenzi si in cazul in care variabila
jwt_token nu a fost folosita, se deschide conexiunea, se introduce 
session_cookie-ul primit la logare intru-un char ** cookies pentru a fi
dat parametru functiei ce returneaza mesajul de cerere. La venirea
raspunsului, exista cazul in care session_cookie-ul era de fapt null, deci 
mesajul afisat este "Nu esti logat!", altfel accesarea bibliotecii are loc 
si se extrage token-ul de acces in variabila jwt_token, dupa modelul
extragerii cookie-ului mai sus. In cazul primirii comenzii enter_library
atunci cand jwt_token este nenul, clientul va primi mesajul "Ai accesat deja
biblioteca!", fara a se rula toate aceste intructiuni.

    GET_BOOKS: In cazul acestei comenzi, se verifica daca jwt_token-ul este
null, pentru a instantia char ** headers cu null, pentru a primi raspunsul
corespunzator. Altfel, se foloseste valoarea jwt_token-ului. Se creeaza
mesajul, se trimite, se primeste raspunsul care poate indica eroarea in urma 
careia sa afiseaza "Nu ai acces la biblioteca!" sau poate indica succesul, 
caz in care se trimite stringul de dupa caracterul "[" functiei extract_books,
astfel afisandu-se informatiile succinte despre toate cartile existente. In
cazul in care nu exista carti de afisat, functia apelata va afisa "Nu exista
carti in biblioteca!".

    GET_BOOK: Comanda asemanatoare celei de dinainte, cu mentiunea ca se
citeste un int id, care indica numarul cartii despre care se solicita date.
Id-ul este citit cu scanf astfel incat sa fie un int si sa fie existent. Astfel
daca nu se introduce nimic, se printeaza mesajul "Introduceti un numar intreg", 
programul asteptand sa citeasca int-ul. Pentru viitoarele citiri, este necesara
golirea bufferului de intrare din cauza citirii cu scanf. Acest lucru se face
prin citirea caracter cu caracter pana la intalnirea lui \n sau EOF. De acesata
url-ul trebuie sa includa id-ul, modificare ce se realizeaza cu sprintf in
variabila url. Se creeaza cererea, la fel, tinandu-se cont de posibilitatea
jwt_token-ului de a fi null. Raspunsul primit poate indica inaccesul la
biblioteca prin lipsa jwt_token-ului sau inexistenta unei carti cu id-ul cerut
sau poate indica succesul cererii, deci si de acesta data prin functia
extract_books, se printeaza toate datele cartii specificate.

    ADD_BOOK: In cazul acestei comenzi, sunt citite noile informatii in
variabilele title, author, genre, page_count si publisher, citirea pentru
page_count fiind facuta dupa modelul citrii pentru id si citirea prin char * 
fiind facuta dupa modelul citirii pentru username si password de la inceput. 
Datele sunt adaugate respectand formatul JSON, in variabila data, impachetata in
body_data. Se creeaza si se trimite cererea, iar raspunsul primit este analizat.
In cazul lipsei tokenului, nu exista autorizare pentru a face modificari asupra 
cartilor deci se afiseaza "Nu ai acces la biblioteca!", altfel cartea se adauga
langa celelalte. Am implementat eroarea de a adauga o carte cu informatii 
introduse incomplet sau care nu respecta formatarea, atunci cand am realizat
citirea, nepermitand introducerea vreunui camp vid si obligand la pastrarea
tipului de date.

    DELETE:  In cazul in care userul doreste sa stearga o carte, se citeste id-ul
dupa modelul citirilor anterioare si se goleste buffer-ul de intrare drept urmare
a citirii folosind scanf. Creez url-ul incluzand id-ul si apelez functia 
compute_delete_request avand ca parametrii ip-ul, url-ul si headerul ce contine 
token-ul, care demonstreaza autorizarea. Functia compute_delete_request a fost
scrisa de mine, avand in minte modelul de cererea necesar si avand drept model
compute_get_request, funtia rezolvata in cadrul laboratorului. Rezultatul cererii 
poate indica una dintre cazurile: nu exista acces la biblioteca, id-ul dat nu se
regaseste printre cartile existente sau cartea dorita chiar a fost stearsa. 

    LOGOUT: Pentru realizarea acestei comenzi, este necesar ca, clientul sa
demonstreze ca este autentificat deci se foloseste session_cookie-ul. Fiind o
cerere de tip get, se apeleaza compute_get_request si se trimite mesajul. In urma
raspunsului de la server, fie nu se realizeaza delogarea pentru ca de fapt clientul
nu este logat, fie se realizeaza cu succes.

    Intre fiecare comanda introdusa, am introdus o printare pentru a fi mai usor 
de urmarit functionalitatea programului. Prin aceasta implementare cu print-uri,
demonstrez realizarea completa a taskurilor deci sunt destul de sigura ca se va ajunge
la o corectura manuala a temei mele pentru ca nu ma asteptam la aparitia unui checker
in ultimele zile si organizarea pe care mi-o facusem nu mi-a permis timpul necesar
modificarilor pentru un punctaj maxim pe checker.