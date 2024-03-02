TEMA 1 - PA 

1. Feribot - Pentru a găsi costul minim, am folosit ideea algoritmului de căutare binară. Am calculat suma 
tuturor costurilor de transport si am luat (1, smax) ca intervalul de căutare, unde smax este suma maxima. 
Pentru fiecare cost din mijlocul intervalului, am verificat daca toate masinile pot fi transportate cu cel 
mult cele k feriboturi date. Dacă da, am micșorat intervalul de căutare către stânga, căutând costul minim,
în caz contrar către dreapta. Variabila smin retine costul minim, in care se va afla rezultatul la sfarsit.

   Asadar functia verificare, cerceteaza daca toate masinile pot fi transportate cu acel cost primit prin 
variabila x. Se parcurge vectorul de greutăți al mașinilor și se numără feriboturile necesare pentru a le 
transporta, iar dacă numărul depășește k, se returnează 0. Altfel, se returnează 1 pentru succes. Funcția 
de verificare are o complexitate de O(n), deoarece parcurge toate elementele vectorului. Căutarea binară 
are complexitatea O(log smax), iar funcția de verificare este apelată in interiorul acesteia de cel mult 
(log smax) ori, deci complexitatea totală a algoritmului este O(n log smax).

3. Nostory - Am preferat sa modific scheletul dat si sa retin cele 2 liste in vectorii a si b alocati dinamic.
Ideea de rezolvare consider ca se incadreaza la algoritmii greedy.

   a)  Pentru taskul 1, m-am folosit de functia sort din biblioteca standard pentru a sorta crecator vectorul
a si descrescator vectorul b. Atfel, la parcurgerea perechilor de la 0 la n-1, suma maximelor din perechi duce
la un scor maxim, netinandu-se cont de numarul de mutari. Complexitatea functiei este data de complexitatea 
sortarii vectorilor, parcurgerea ulterioara a perechilor avand O(n). Deci functia are complexitatea O(n*log n)
din cauza algoritmului quicksort care imparte in mod recursiv in liste mai mici, pe care se sorteaza ulterior.

   b)  Pentru taskul 2, am folosit 2 cozi de prioritati: v_max_pq pentru maximele fiecarei perechi, iar 
v_min_pq pt minime. La fiecare adaugare a unui numar, insertie se face astfel incat v_max_pq sa fie ordonat 
descrescator, iar v_min_pq crescator. Totodata in acesta parcurgere se calculeaza scorul (suma) pentru liste
in forma in care se dau. Ulterior in limita mutarilor posibile si cat timp este avantajos, se inlocuieste in 
calculul sumei cate un numar minim din vectorul numerelor maxime v_max_pq cu un numar maxim din v_min_pq. Se 
returneaza suma in functia main unde este afisata. Complexitatea unei cozi de prioritati este O(log n) si din 
moment ce se insereaza de 2 ori cat n elemente, avem O(2n*log n). Iar la percurgerea pt mutari sunt un nr de
moves mutari * O(log n). Deci complexitatea functiei este O((n + moves) * log n).

4. Sushi - Ideea de rezolvare se incadreaza in tehnica de programare dinamica.

   a)  In functia taskului 1, am folosit 2 vectori last_line si current_line pentru a retine ultima linie si 
linia curenta, folositi in gasirea solutiei. Pentru inceput, se calculeaza sumele preferintelor prietenilor 
pentru fiecare platou in parte, in vectorul sum_pref. Apoi pentru fiecare platou, se parcurg sumele de bani 
posibile de la 1 leu pana la suma maxima de bani, retinuta in variabila max, obtinuta din (n prieteni * x lei).
 Vectorii ce retin cele 2 linii au initial toate valorile 0. La fiecare pas se verifica daca banii (variabila 
 lei) sunt suficienti pentru a cumpara platoul curent (p[i]), iar in caz negativ, se retine suma posibila a 
 notelor obtinuta cu acei bani la pasul anterior. Daca sunt suficienti bani, se cumpara platoul curent prin 
 calcularea in variabila sol_aux a sumei notelor platoul curent si a sumei notelor platorilor anterioare 
 disponibile cu restul de bani. In acest caz valoarea liniei curente pentru acei lei va fi maximul dintre 
 valoarea retinuta in variabila sol_aux si valoarea de la pasul anterior in care nu se cumpara platoul curent. 
 Din moment ce nu am folosit o matrice, este nevoie de circularitate deci current_line trebuie sa devina 
 last_line, pentru fiecare platou nou. Rezultatul este retinut in linia curenta pe pozitia numarului maxim de 
 lei.

    Complexitatea acestei functii este O(m * n * x + n * m) = O(m * n * x), pentru n - numărul de prieteni, 
m - numărul de platouri si x - suma maxima de bani pe care fiecare prieten poate contribui. Primul ciclu for 
de calcul al preferintelor prietenilor are o complexitate de O(n * m), iar cel de al doilea are complexitatea 
O(n * m * x), inlocuind cu variabila folosita de mine fiind O(m * max).

   b) Taskul 2 este similar taskului 1, cu cateva modificari. Este necesara inca o varibila sol_aux deoarece
maximul notelor va fi ales de aceasta data din 3 posibiliati: suma notelor platorilor de la pasul anterior, 
sol_aux1 care retine suma notei unui platou curent si suma notelor platourilor cumparate cu restul de bani si 
a treia posibilitate: sol_aux2 care retine dublul sumei notelor corespunzator pt 2 platouri de la pasul curent 
adunat de asemenea cu suma notelor platourilor cumparate cu restul de bani. Aceasta variabila sol_aux2 va fi 
calculata doar atunci suma de bani (retinuta in "lei") este suficienta pt a cumpara 2 platouri de acelasi tip. 
In rest functia este asemanatoare cu cea de la taskul 1, avand aceeasi complexitate O(m * n * x).

   c)  Plecand de la codul taskurilor precedente, pentru taskul 3 am folosit vectorii last_line si 
current_line, doar ca de aceasta data le-am mai adaugat o dimensiune de lungime maxim n + 1 (pozitia 0 este 
neutilizata). Ideea algoritmului este ca pentru fiecare platou, pentru fiecare suma de bani, sa se retina si 
numarul maxim de platouri pentru care se calculeaza suma notelor prietenilor. Deci in functie de acest indice, 
am impus in plus conditia ca acesta sa fie > 1 pt cazul in care se cumpara 2 platouri de acelasi fel. Atunci 
cand se cumpara unul sau 2 platouri, e nevoie de nota preferintelor prietenilor de la pasul precedent (last_line) 
corespunzatoare banilor ramasi (lei - p[..]) si corespunzatoare numarului de platouri disponibile de cumparat
 (j - ..). In rest algoritmul are la baza ideea descrisa mai sus. Din cauza for-ului interior adaugat,
 complexitatea devine O(m * n^2 * x). Acest subpunct mi s-a parut cel mai greu din toata tema pt ca mie mi-a luat
 mult sa mi dau seama care e abordare ce duce spre solutia eficienta. Am incercat initial in mai multe feluri, dar
 care nu garantau solutia corecta pt toate testele.

 5. Semnale - Am rezolvat aceasta problema plecand de la acceasi tehnica, progrmare dinamica, si m-am folosit de
 modul de stocare a datelor cu cei 2 vectori current_line si last_line, ca in problema precedenta.

    a)  Am vizualizat rezolvarea ca o matrice in care randurile reprezinta nr de biti de 0, iar coloanele numarul de 
biti de 1 cu care se pot construi semnalele. In functie am implementat utilizand vectorii current_line si last_line,
iar pt parcurgerea intregii matrice,la finalul fiecarui rand last_line ia valorile lui current_line. In "matrice" 
am completat manual prima linie si prima coloane conform cerintei acetui task. Am considerat ca se poate crea un
semnal cu 0 biti de 0 si cu 0/1 biti de 1. Dar cu 0 biti d 0 si 2 biti de 1, nu se poate creea niciun semnal pt ca
nu pot exista 2 biti de 1 consecutivi. Restul valorilor sunt initial 0. Luand un exemplu, am gasit relatia de
recurenta prin care elementul de la pasul curent este suma dintre elementul cu acelasi nr de biti de 1, dar cu 
i - 1 biti de 0 si elementul cu j - 1 biti de 1 si i - 1 biti de 0. Astfel ca numarul cautat se afla pe randul x si
coloana y. Rezulatatul se va afla astfel pe randul x si coloana y. 

    Complexitatea functiei este O(x * y) deoarece exista un ciclu care se executa de y ori in interiorul unuia care
se executa de x ori, in interior aflandu-se doar operatii care au complexitatea O(1).

    b)  In rezolvarea taskului 2, am plecat de la rezolvarea taskului 1 si am modificat conditia de a exista 3 cifre
de 1 alaturate. Deci in initializarea primului rand, am marcat crearea unui semnal cu 0 biti de 0 si 2 biti de 1 si 
lasat 0 semnale create pt 0 biti de 0 si 3 biti de 1. Iar de data asta, in crearea solutiei la fiecare pas, se 
insumeaza numerele cu i - 1 biti de 0 si cu j, j - 1 si j - 2 biti de 1. In construirea coloanei 2, se considera caz 
separat ca in care se insumeaza doar 2 numere, neexistand cel de-al treilea. In mod similar, rezultatul se afla pe 
pozitia din dreapta jos a "matricei", randul x si coloana y.

    Complxitatea ramane neschimbata, O(x * y) deoarece modificarile aduse functiei au complexiteatea O(1).
