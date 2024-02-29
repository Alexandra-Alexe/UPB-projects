# TEMA1 - Elemente de grafica pe calculcator 

# Init:

In functia Init, initializez variabilele de care voi avea nevoie 
ulterior, grupate in functie de utilizare. Tot acolo, creez cadrul jocului 
prin vertecsi si indici: dreptunghiul rosu pentru linia de finish, patratele 
verzi pentru plasarea armelor si inimile rosii, simbolizand cele 3 vieti 
disponibile in joc si cadranele in care se afla cele 4 arme. Mi-am creat 3 
functii de tip CreateMesh, pentru a evita codul duplicat in crearea stelelor,
armelor si hexagoanelor. Am pus aceste 3 functii intr-un fisier separat,
mesh_func.cpp.

# Mesh_func 

Forma de hexagon a inamicilor este gandita cu centrul in originea axelor 
de coordonate. Practic inamicul este reprezentat de o singura figura cu 2 
hexagoane suprapuse. Pentru a se distinge 2 culori diferite pentru fiecare 
hexagon, exista 2 puncte pentru centru, unul de fiecare culoare. Arma este 
formata dintr-un romb si un dreptunghi suprapuse. In crearea stelei, am definit 
toate cele 10 puncte, 5 interioare, 5 exterioare si le-am grupat in triunghiuri 
pentru a crea forma de stea. Toate cele 3 forme au fost gandite de la inceput 
astfel incat sa aiba toate varfurile pe raza unui cerc cu aceeasi raza. La 
apelarea acestor functii, se indica culoarea formei dorite prin cei 3 parametrii 
R, G, B, iar forma creata este adaugata in lista de mesh-uri prin string-ul 
sugestiv dat, de exemplu "hexagon_roz", "romb_albastru", etc. 

# Update

In primul rand, in functia update sunt desenate la fiecare frame, 
elementele statice ale scenei de joc: drepunghiul - linie de finish, cele 9 
patrate verzi pentru plasarea armelor, cadrenele incadratoare, cele 4 arme de 
culori diferite si pretul fiecareia sugerat prin stelute de dedesubt. In functie 
de valoarea variabilei lives, se deseneaza inimioare sugerand numarul de vieti ramase. 

Mi-am construit o structura Stele cu campurile x si y, drept coordonate. Cu
ajutorul unui vector de acest tip am tinut evidenta stelutelor ce apar random pe ecran 
pentru a fi colectate. La fiecare interval de timp definit in Init, spawnInterval_star,
se genereaza 3 seturi de 2 numere random pentru coordonatele viitoarelor 3 stelute, si 
se adauga toate in vectorul v_stele. Ulterior se parcurge tot vectorul si se afiseaza 
toate stelutele existente in fereastra jocului.  Prin variabila stars_no, se cunoaste 
numarul de stelute-coins stranse, si acest numar este indicat de stelutele desenate sub 
lives.

In functia OnMousePress, se parcurge vectorul de stelute, v_stele si daca butonul 
stanga a fost apasat in interiorul dreptunghiului din jurul unei stelute, aceasta este 
stearsa din vector.

# #   Enemy clasa + generare + desenare + func_enemy

Evidenta  inamicilor o retin intr-o matrice de 3 x 3, deoarece exista 3 linii 
posibile pentru aparitia acestora si deoarece am considerat ca la un moment de timp nu pot
fi prezenti mai mult de 3 inamici pe o linie. Matricea contine elemente de clasa Enemy, pe
care am definit-o separat. Fiecare inamic este definit prin: 
- x si y(coordonatele pentru plasarea in scena), 
- start_point(valoarea de start pentru deplasarea pe Ox), 
- culoare,
- counter(prin care se contorizeaza numarul de lovituri primite -> la 3 lovituri, 
inamicul fiind distrus), 
- scale si scale_start (prima variabila se foloseste la scalarea inamicului in 
momentul in care trebuie sa dispara prin scalare catre 0, iar a doua scale_start are aceeasi 
valoare pentru toti inamicii si reprezinta valoarea de la care se incepe scalarea), 
- occupied(variabila de tip bool prin care se cunoaste daca exista la momentul curent
 un inamic desenat pe acea pozitie din matrice) si 
- disappear ( variabila setata pe true in momentul in care inamicul trebuie sa
dispara).
       Pentru aceste variabile, in clasa Enemy exista setteri si getteri prin care sa modifica 
sau sa acceseaza aceste campuri.

Utilizare matricei de inamici in functia update, se face in primul rand la generarea 
de inamici noi. Ma folosesc de un interval de timp definit initial si de o variabila in care
masor timpul pentru a genera random linia si culoarea inamicului la anumite intervale de timp.
Iau fiecare coloana din matrice de la stanga spre dreapta, in ordine pentru adauga inamicul, 
moment in care campurile specifice sunt setate corespunzator(occupied devine true; counter-ul 
devine 3, disappear devine false, etc), inclusiv culoarea. Se face apoi apelul functiei 
DrawEnemy unde se va folosi matricea de inamici, deltaTimeSeconds, numarul de vieti, numarul
 de linii si de coloane din matrice. 

In aceasta functie, se parcurge matricea de inamici si pentru fiecare se verifica prin
variabila occupied daca acesta trebuie desenat. Apoi se verifica daca inamicul a ajuns la linia
de finish, caz in care numarul de vieti scade, inamicul de pe acea pozitie va avea variabila 
occupied false, si variabila x se reseteaza la valoarea de start. Altfel, daca deplasarea 
inamicului spre stanga nu ajunge la capat, se scade variabila x si se apeleaza o functie seaprata
 MoveOrDisappearEnemy prin care se acopera cele 2 cazuri: deplasarea propriu-zisa si scalarea 
 catre 0 pana la disparitie. Acest lucru se decide prin verificarea campului disappear. In cazul
deplasarii spre stanga, se folosesc transformarile 2D, aplicate pe modelMatrix, translatie
fiind ultima. In cazul scalarii catre 0, se utilieaza si campul scale al inamicului care 
este decrementat. Atunci cand scale ajunge mai mic ca 0, toate campurile sunt resetate creand
cadrul initial.

# #  Gun clasa + generare + drag and drop + desenare + func_gun

Voi incepe sa descriu generarea armelor din functia OnMouseBtnPress, acolo unde se verifica
daca a fost apasat butonul stanga al mouse-ului si apoi se apeleaza functia WhichGunToDrag pentru
a fi identificata culoarea armei. Toate functiile legata de arme sunt puse in fisierul 
func_gun.cpp. Deci functia WhichGunToDrag verifica ca la click, mouse-ul sa se afla pe una dintre 
arme, se marcheaza incepearea tragerii de arma prin variabila drag, se retine culoarea acesteia in
variabila color; totul numai daca numarul de stelute stars_no este mai mare sau egal cu pretul 
armei dorite.

In functia update se verifica daca variabila drag este activata, astfel incat sa se afiseze 
la fiecare moment de timp rombul pe masura ce este tras. Deci prin functia Drag se face traslatie
la coordonatele mouse-ului.

In momentul in care se face release, ma asigur ca variabila drag a fost activata inainte, o
dezactivez punand-o pe 0 si apelez functia WhichGreenSquare pentru a vedea pe care din cele 9 
patrate trebuie plasata arma. In aceasta functie se identifica care dintre patrate se afla mouse-ul,
iar daca pozitia din matricea de arme este disponibila, se apeleaza functia BuildGunMatrix prin care
se seteaza toate campurile armei pentru acea pozitie. Tot aici, la plasare, numarul de stelute scade 
cu pretul armei alese. Asadar matricea matrix_gun tine evidenta armelor plasate pe cele 9 patrate 
verzi posibile.

In functia de OnMouseBtnPress se acopera si cazul in care se face click drepata pe o arma 
deja plasata. Deci daca a fost apasat butonul drepata al mouse-ului, ma folosesc de aceeasi functie
WhichGreenSquare pentru a determina despre care arma este vorba mai exact si ii modific campul 
Disappear pe true, pentru ca la afisarea sa declaseze procesul de scalare catre 0. 

Asadar in functia Update se ia fiecare arma existenta in matrice, care are campul 
occupied = true, si se apeleaza alta functie DrawOrDisappearGun. Acolo, in functie de valoarea 
campului disappear se face  desenarea continua sau scalarea catre 0, folosind campul specific scale 
si se tine cont ca atunci cand arma dispare, campurile se fie resetate in forma de inceput. 

# # Coliziune arma - inamic

Coliziunea dintre arma si inamic este detectata prin
parcurgerea celor 2 matrice care tin evidenta acestora si daca exista un inamic si o arma pe
aceeasi linie, iar distanta dintre centrele acestora este mai mica decat suma razelor, campul 
disappear al armei este marcat ca true si este apelata functie DrawOrDisappearGun.

# # Proiectiele constructie + desenare + func_shoot

Aparitia proiectilelor se face prin parcurgerea matricei de arme, iar pentru fiecare se 
apeleaza functia CanShoot pentru fiecare dintre cele 3 serii de inamici care pot aparea. Aceasta 
functie se asigura de potrivirea culorii si ne spune daca proiectilul poate fi generat. Daca exista
mai multe serii de inamici prezente pe o linie, se va trage in cel mai apropiat. Ulterior se parcurge
vectorul de proiectile pentru a determina daca exista deja un proiectil generat din arma respectiva. 
In caz afirmativ, se cerceteaza daca intervalul de timp dintre proiectilele aceleiasi arme s-a scurs,
fapt marcat prin variabila foundIndex. Deci adaugarea unui nou proiectil in vector se face daca se poate
trage si proiectilul nu a mai fost generat pana acum sau daca proiectilul a mai fost generat dar a trecut
timpul si se poate trage altul.

Pentru a desena proiectilele, parcurg vectorul v_shot, ma asigur ca acestea nu au iesit din scena,
caz in care le sterg din vector, si daca nu are loc o coliziune, le desenez la coordonatele specifice. Tot
aici modific campurile angularStep, x si spawnTime prin care se face translatia, rotirea si scurgerea 
timpului. 

# # Coliziune proiectil - inamic

Atunci cand se face parcurgerea vectorului de proiectile si se detecteaza faptul ca centrele 
proiectilului si al inamicului sunt mai apropiate ca suma razelor, counter-ul inamicului este decrementat 
si glontul este sters din vector. In cazul in care counter-ul a ajuns la 0, adica cand inamicul a fost 
lovit de 3 proiectile, inamicul de pe acea pozitie din matrice este marcat cu true in campul disappear 
astfel incat la viitoarea desenare, acesta sa fie scalat catre 0 si sa dispara. 

In implementare mi-am creat functiile getMyLogicX si getMyLogicY pentru a traducerea din 
coordonatele mouse-ului in coordonatele scenei mele. De asemenea, functiile getOxGun si getOyGun ajuta 
in implementare pentru a determina exact pozitia pe care trebuie o arma sa fie plasata in functie de 
indicele sau din matrice.
