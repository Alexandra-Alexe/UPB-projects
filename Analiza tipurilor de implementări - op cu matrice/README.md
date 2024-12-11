## Analiza tipurilor de implementări - op cu matrice 
# Tema 3 - ASC 


1. Implementarea BLAS

Pentru a nu pierde valoarea matricei B in calcule, consider 2 copii ale sale, matricele D si E.
Copiile le realizez cu ajutorul functiei cblas_dcopy numarul de elemenete ce trebuie copiate, 
matricea sursa si destiantie si incrementul pentru vectorii sursa si destinatie.  Pentru 
inmultirile ce includ matricea A, am folosit functia cblas_dtrmm care este proiectata astfel incat
 sa tina cont ca una dintre matrici este superior / inferior triunghiulara. Asadar profit de acest 
 lucru pentru a minimiza timpul de rulare. Cu ajutorul parametrilor specific faptul ca matricile 
 sunt stocate pe randuri, faptul ca vreau ca inmultirea sa se efectueze intr-o anumita ordine si 
 tot prin parametrii specific acolo unde este cazul daca vreau sa una dintre matrici sa fie 
 transpusa. Deci se efectueaza cele 2 inmultiri din interiorul parantezei si se retin rezultatele 
 in matricile D si E. Apoi acestea 2 se aduna cu ajutorul functiei cblas_daxpy, iar in final se
  efectueaza o inmultire intre 2 matrici generale, rezultatul adunarii, retinut in E si B tranpus.

2. Implementarea neoptima

Am construit functii separate pentru fiecare functionalitate, functii pe care doar le-am apelat in
 ordinea corecta in my_solver, pastrand ordinea operatiilor. Pentru inmultirea matricilor am tinut
  cont de faptul ca matricea A este superior triunghiulara astfel ca am construit 2 functii de 
  inmultire mai eficiente pentru cele 2 cazuri in care apare A in inmultire:
- multiply_efficent_lower_triangular primeste o matrice A, inferior triunghiulara si o matrice B,
 oarecare. Se efectueaza inmultirea clasica, retinandu-se rezultatul in matricea result, cu 
 precizarea ca indicele k al for-ului cel mai interior este limitat la valoarea curenta a lui i, 
 fiindca altfel s-ar efectua inmultiri si adunari cu 0 care nu ar schimba cu nimic rezultatul, deci
  am salvat timp.
- multiply_efficent_upper triangular primeste o matrice oarecare A si o matrice B, superior 
triunghiulara. Implementarea este asemanatoare cu cea de mai sus, cu precizarea ca de aceasta data
 limita indicelui k este data de valoarea lui j deoarece B dicteaza de la ce punct in colo urmeaza 
 valorile de 0.
- multiply este functia clasica pentru inmultirea a doua matrici, fiind necesara la ultima inmultire
 din formula data spre calcul. In acest caz k va lua valori de la 0 la N.
- functia transpose returneaza matricea transpusa pentru o matrice data
- functia add aduna elementele de pe fiecare pozitie pentru 2 matrici date si returneaza rezultatul

3. Implementarea optima

Am inceput implementarea optima pornind de la codul pentru implementarea neoptima, incarcand sa 
fac optimizari. Asadar rationamentul este acelasi ca mai sus, cu urmatoarele adaugari:
- am folosit keyword-ul register in cazul indicilor pentru pozitiile din matrice si a pointerilor
intrucat am dorit ca datele sa fie stocate in registrele procesorului, astfel elimandu-se 
overhead-urile de acces la memorie. 
- am renuntat la calculul clasic al indicilor din matrice si am inlocuit prin folosirea pointerilor.
Asadar am incrementat pointerii pentru fiecare pozitie din matrice sau pentru fiecare termen din 
suma, scazand numarul total de operatii efectuate. 


Am atasat arhivei fisierele neopt.memory, blas.memory si opt_m.memory din care se poate observa faptul
ca nu exista probleme de acces la memorie.


# Analiza celor 3 implementări folosind cachegrind


1. blas.cache 

- I refs =  248,604,423 reprezintă numărul total de instrucțiuni executate de program, despre care se poate
spune ca era de asteptat sa fie un numar mare intrucat vorbim de un program intensiv in executie. 
- Din valorile ratelor de ratare ale cauche-ului pentru instructiuni, se poate trange concluzia ca majoritatea
instructiunilor sunt găsite în cache-ul de nivel 1, rata de ratare a cache-ului de ultim nivel pentru 
instructiuni fiind practic neglijabila 0.00%.
-  D refs: 94,659,536  (87,474,634 rd   + 7,184,902 wr) , numarul de referinte de date este semnificativ, 
cu o proportie mare de citiri în comparație cu scrieri, reflectand natura operatiilor matematice intense.
- Rata de ratare a cache-ului L1 pentru date este de 1.9%, ceea ce este rezonabil pentru un program de acest
 tip. Rata de ratare a cache-ului de ultim nivel pentru date este foarte mică 0.1%, indicand o buna
 localizare a datelor.
- Branches: 5,875,538, Mispredicts: 67,732 - numarul total de ramuri si rata de mispredict sunt în limitele
 asteptate pentru un program cu calcule complexe. Rata de mispredict de 1.2% indica un sistem de predictie
  a ramurilor destul de eficient.

2.  neopt.cache 

- I refs: 3,632,622,593 , numarul de referinte de instructiuni este mult mai mare, comparativ cu implementarea 
BLAS,  indicand un program categoric mai ineficient.
- Rata de ratare a cache-ului L1 pentru instructiuni este foarte mica 0.00%, dar acest lucru nu compensează 
numărul mare de instructiuni executate
- D refs: 1,947,232,347 (1,813,686,143 rd   + 133,546,204 wr) numarul de referinte de date este semnificativ
 mai mare decat in implementarea BLAS, indicand o utilizare mai intensa a datelor, ceea ce contribuie la 
 ineficienta programului.
- Rata de ratare a cache-ului L1 pentru date este semnificativ mai mare 5.8% comparativ cu implementarea 
BLAS 1.9%. Aceasta sugereaza o localizare slaba a datelor, ducand la frecvente accesari ale memoriei principale.
- Branches: 133,812,847  Mispredicts: 503,412 , numarul de ramuri executate si rata de mispredict sunt mai mari
comparativ cu implementarea BLAS, in concordanta cu ineficienta acestei implementari.

3. opt_m.cache

- I refs: 2,217,268,413, implementarea optimizata are un numar de referinte de instructiuni intermediar 
intre implementarea BLAS si cea neoptimizata. Aceasta sugereaza ca optimizarile aduse au redus numarul total
 de instructiuni, dar nu la nivelul extrem de optimizat al bibliotecii BLAS. 
- Implementarea optimizata reduce numarul de referinte de instructiuni si date comparativ cu implementarea 
neoptimizata, dar nu atinge eficienta extrema a implementarii BLAS
- D refs: 464,984,844  (460,561,025 rd   + 4,423,819 wr) Pentru numarul de referinte de date este valabil acelasi
lucru, el indica o valoare intermediara intre celelalte 2 implementari.
- Ratele de ratare pentru cache-ul de date sunt ridicate, in special pentru cache-ul de nivel 1 (D1 miss rate de 
24.3%),indicand o problema persistenta cu localizarea datelor.
- Branches: 133,813,084 Mispredicts: 503,448  Ratele de predictie gresita pentru ramuri sunt similare intre 
implementarile optimizata si neoptimizata, sugerand că optimizarile nu au avut un impact semnificativ asupra 
structurii de control a programului.

In cazul acestei implementari trebuie sa mentionez utilizarea specificatorului register a redus numarul de 
accesari ale memoriei si a instructiunilor necesare pentru manipularea variabilelor, astfel ca valorea I refs
a scazut semnificativ. Rata de ratare a cache-ului de instructiuni este similara in implementarile optimizata 
si neoptimizata, dar mult mai mica decât in BLAS, ceea ce sugereaza ca accesul rapid la registre a redus 
presiunea asupra cache-ului.
De asemenea, inlocuirea expresiilor aritmetice directe cu pointeri incrementati a redus numarul de operatii de
multiplicare. Scaderea semnificativa a numărului de referinte de date indica faptul ca optimizarea calculului 
indicilor a fost o alegere buna.


# Analiza grafic 

Am creat un fisier de tip json in care am stocat rezultatele rularii celor 3 implementari asupra a 5 valori
pentru dimensiunea matricei (N = 400, 800, 1200, 1400, 1600). Ruland fisierul graphics.py, se obtine graficul urmator:

![image](image.png)

Am atasat graficul in format png si separat, in arhiva. 
Analizand graficele, pentru N cu valori intre 400 si 1600, pot spune ca:
- In medie opt_m este cu aproximativ 65.94% mai rapid decat neopt
- In medie blas este cu aproximativ 86.71% mai rapid decat opt_m.
In concluzie, performantele metodei blas sunt remarcabile pe tot intervalul analizat, mentinandu-se superioare 
celorlalte metode ai demonstrând o scalabilitate aproape liniara. Metoda opt_m reprezinta o imbunatatire clara
fata de metoda neopt, dar nu se compara cu eficienta metodei blas. Metoda neopt este cea mai ineficienta, cu 
timpi de executie care cresc exponențial cu N.