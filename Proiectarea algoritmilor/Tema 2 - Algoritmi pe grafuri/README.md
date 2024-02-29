TEMA 2 - PA 

Am ales sa implementez tema in limbajul C++ si am rezolvat problemele:
supercomputer, ferate si, in mod partial, magazin.

1.Supercomputer

Ideea rezolvarii problemei a plecat de la sortarea topologica. Dupa mai 
multe incercari am combinat ideea algoritmului lui Kahn cu principiul programarii 
dinamice deoarece fara dp, nu as fi ajuns la un algoritm atat de eficient.
Astfel complexitatea este O(n+m), n fiind nr de noduri, dat de partea in care
initializeaza coada, de exemplu, iar parcurgerea cozii si actualizarea gradelor 
interne presupune parcurgerea fiecarei muchii odata deci, de aici m.

Algoritmul citeste datele de intrare si retine graful sub forma unei liste de
adiacenta, graph, si retine setul de date cerut de fiecare task(nod) in vectorul
dataSet. Pe masura ce se construieste graful, in vectorul inDegree se memoreaza
gradul intern al fiecarui nod. Se apeleaza functia calculate() care intoarce sub
forma unui int, nr minim de context switch uri, care se afiseaza.

Functia calculate() utilizeaza o coada q, in care se vor introduce la fiecare
pas nodurile cu gradul intern 0, parcurgandu-le conform dependentelor. Vectorul dp 
are n elemente, initial nule, care vor reprezenta lungimile cele mai lungi de la 
nodul de inceput pana la nodul i, in care fiecare nod solicita un set diferit de 
date. Initial, se introduc in coada toate nodurile cu gradele interne 0, si 
ulterior cat timp nu se goleste coada, pentru fiecare nod in ea, se decrementeaza
inDegree ul, si se adauga in coada daca ajunge la 0, si se recalculeaza valoarea
din vectorul dp ca maximul dintre valoarea curenta a dp[i] si valoarea dp[nod
 parinte] + 1, daca trecerea din nodul parinte in nodul i reprezinta si ea un
 context switch. La final, rezultatul minim va fi maximul dintre valorile 
 vectorului dp, deoarece cautand valoarea maxima, se gaseste cea mai lunga cale 
 posibila in care fiecare nod are un set diferit de date fata de nodul precedent.
 Acesta va reprezenta numarul minim de context switch uri necesar parcurgerii
 grafului in ordinea impusa.

 2.Ferate 
 
Ideea rezolvarii problemei se bazeaza pe algoritmul tarjan, prin care identific
componentele tari conexe. Ulterior reazlizez un nou graf in care fiecare componenta
tare conexa reprezinta un nod, iar acest graf este analizat pentru a obtine numarul
minim de muchii(linii ferate) ce trebuie constuite. Functia tarjanDFS are complexitatea
O(n+m), dar aceasta este apelata in functia tarjan de n ori. Complexitatea functiei main
se poate neglija comparativ cu celelalte complexitati. Iar functia buildNewGraph are o
complexitate de O(n+m) deoarece se parcurg toate nodurile din componentele tari conexe
 si muchiile. Asadar complexitatea dominanta codului este O(n*(n+m)).
 
Algorimtul citeste nr de gari, nr de linii ferate, gara si apoi muchiile, creand
in acelasi timp graful, sub forma unei liste de liste. Functia tarjan este apelata pe
graf si intoarce componentele tari conexe, sub forma unui vector de vectori. Apoi
cu ajutorul functiei buildNewGraph construiesc noul graf folosind components si graful
initial. Cum am zis, in graful nou am considerat ca o componenta conexa este un nod
nou si am pastrat muchiile intre componente. Este important sa stiu din ce componenta
tare conexa face parte nodul-depozit asa ca parcurg toate componentele si retin acest 
lucru in variabila x. Numarul minim de linii ferate care trebuie construite este egal
cu numarul de componente tari conexe in care nu se poate ajunge (care au gradul intern
0), cu o singura exceptie. Daca depozitul face parte dintr-o componenta tare conexa cu
grad intern 0, aceasta componenta nu trebuie luata in calcul la numar pentu ca
transportul se face de la depozit, nu spre depozit. Asadar parcurg noul graf, calculez
gradele interne si apoi aflu nr de noduri cu grade interne 0, dupa cum am spus mai sus.
Deci acest numar reprezinta rezultatul.

Functia tarjan va aplica o parcurgere pe fiecare nod, asigurandu-se ca nu se aplica
de mai multe ori pe un nod. Parcurgerea se va face de fapt, prin apelare functiei
tarjanDFS. Vor fi necesari mai multi vectori care au fost declarati aici: un vector ce 
retine indicii fiecarui nod pe parcursul parcurgerii, un vector de retine valoarea de
low link, cu ajutorul careia se vor determina comp tari conexe, un vectori de
vectori in care se vor retine comp tari conexe, o stiva si un vector ce retine despre
fiecare nod daca a fost sau nu pus in stiva. Variabila id se foloseste pentru a
contoriza numarul comp tari conexe.
    
In functia tarjanDFS se parcurge nodul prin modificarea index[node] si lowlink[node] 
cu id-ul la care s-a ajuns,se pune pe stiva si se marcheaza acest lucru. Fiind DFS,
pentru vecinii nevizitati (care au index[neighbor] = 0), se apeleaza tarjanDFS. La
intoarcerea din recursivitate se modifica lowLink-ul astfel incat se fie minimul dintre
lowLinkul curent si lowLinkul vecinului la care am fost. Si daca se ajunge intr-un nod in 
care am mai fost, se modifica doar lowLinkul, la fel pastrandu-se minimul. Componenta tare
conexa este identificata atunci cand, intorcandu-ne din recursivitate, ajungem la un nod
care indexul egal cu lowLinkul, caz in care toate nodurile din stiva din acel moment se pun
intr-un vector al vectorului components si se marcheaza ca s-au scos de pe stiva.
    
Pentru a face mai eficienta functia buildNewGraph, am realizat o mapare intre nodurile
initiale si componentele tari conexe existente. Apoi pentru fiecare componenta tare conexa,
pentru fiecare nod al ei, pentru fiecare vecin al nodului verific componenta celui din urma
este diferita de componenta curenta, caz in care trebuie sa pastrez acea legatura intre
componente. Iau in considerare cazul in care legatura a mai fost adaugata, pentru a nu o
adauga de 2 ori. 

3.Magazin

Tinand cont de cerinta, mi-am dat seama ca trebuie sa abordez aceasta problema folosind
algoritmul de dfs. Complexitatea rezolvarii este data de parcurgerea in adancime inmultita cu
numarul de intrebari deci este O((n+m)*q), unde m este nr de muchii, adica in cazul nostru
O(2n*q), pentru n - nr de noduri si q - nr de intrebari.
    
Se citesc datele de intrare si se construieste graful sub forma unei liste de adiacenta.
Asa cum am procedat si in celelalte probleme, am indexat graful de la 0 si am avut grija in
calcul si la afisare. Intrebarile le-am stocat intr-un vector ("perechi") de vectori cu 2 
elemente, in care primul numar indica depozitul de la care incepe expedierea si al doilea
reprezenta numarul de expedieri consecutive. Pentru fiecare intrebare am considerat un vector
visited in care initial toate nodurile sunt nevizitate. Pentru fiecare intrebare se apeleaza
functia dfs si se afiseaza fie depozitul la care s-a ajuns, fie -1 in cazul in care nu se poate
efectua acel nr de expedieri.
    
In functia dfs se verifica daca s-a epuizat numarul de expedieri pentru a retine rezultatul
si a incheia funcia. Altfel se marcheaza ca vizitat nodul curent si pentru vecinii nevizitati
se apeleaza iar functia dfs dupa ce se decrementeaza nr de expedieri. Deci functia se opreste
dupa ce se realizeaza un nr de exp expedieri.
