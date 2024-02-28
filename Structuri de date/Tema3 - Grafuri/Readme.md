									
								TEMA  3   SD

	In functia main sunt citite datele de intrare si este contruita matricea de adiacenta, in
 care se marcheaza existenta unui arc intre noduri prin atribuirea costului. Vectorul deposits	
are valorea 1 pe nodurile care reprezinta depozite. Se citeste numarul de task-uri
si id-uk fiecaruia.
	~ Task-ul 1: Variabila s retine depozitul in care se incarca marfa, iar k -  nr de magazine
aprovizionate. In vectorul stores se retin nodurile ce reprezinta magazine de aprovizonat.
Pentru fiecare astfel de magazin se calculeaza in variabilele d1 si d2, distanta de la depozit
la magazin si de la magazin la depozit. Este utilizata functia dijkstra care modifica valoarile
lui d1 si d2 si realizeaza afisarea acestora. In final, este afisata distanta totala retinuta in
variabila totaldist. 
	~Task-ul 2: Se utilizeaza functia plusminus.

Functii:
	-- Functia dijkstra primeste ca parametrii graful, doua noduri, unul pe post de sursa, iar
celalalt pe post de destinatie, un parametru path utilizat pentru a indica daca se doreste
afisare si variabila dist pentru valoarea distantei. Initial vectorul pentru calculul distantelor
este initializat cu o valoare foarte mare, vectorul ce retine nodurile vizitate are valorile 0, iar
vectorul parent are toate valorile -1. Cel din urma, va fi utilizat pentru afisare. Distanta
nodului sursa va pleca de la 0. Restul nodurilor vor fi parcurse in ordinea minima a distantei.
Functia ce calculeaza si returneaza acest lucru in variabila u, este mindistancenode. Nodul 
curent, u, este marcat ca vizitat, iar apoi pentru restul nodurilor nevizitate, j, catre care 
exista arc dinspre nodul curent, se verifica daca distanta nou calculata este mai mica decat 
cea din vectorul distance, caz in care se face modificarea. Distanta noua se calculeaza ca
suma dintre valoarea vectorului distance pe pozitia u si valoarea costului drumului de la u 
la j. In cazul in care se modifica distanta, se marcheaza si in vectorul parent faptul ca de la 
nodul u se urmeaza drumul catre nodul j, deci nodul u este nodul parinte. In cazul in care
parametrul path are valoarea 1, se apeleaza functia de afisare.
	-- Functia mindistancenode are ca parametrii graful g, vectorul de distante si cel in care
sunt marcate nodurile vizitate. Cu ajutorul unei varibile min, se cauta nodul nevizitat cu 
distanta cea mai mica care va fi returnat.
	-- Functia printPath primeste ca parametrii vectorul parent, un nod sursa si unul
destinatie. Daca nodul destinatie nu are parinte, ci are inca valoare initiala -1, nu exista
drum catre acesta. Altfel functia se autoapeleaza de fiecare data pentru nodul parinte, 
realizandu-se astfel afisarea acestora.
	--Functia plusminus numara in variabila nrcomponents componentele tari conexe. Se
utilizeaza vectorul component pentru a faptul ca un nod face parte dintr-o anumita
componenta, vectorul viz ce retine nodurile vizitate, vectorii plus si minus ce vor ajuta la 
parcurgerea normala si inversa a nodurilor. Initial vectorii viz si component au toate valorile
nule. Pentru fiecare nod nevizitat, care nu e depozit, creste numarul de componente conexe,
vectorii plus si minus iau valorea 0 si se realizeaza apelul functiei recursive, o data cu
parametrul 1 si o data cu parametrul 0 pentru a realiza parcurgerea in ambele feluri. In
urma acestor parcurgeri, daca vectorii plus si minus au valoarea 1 pe pozitia unui nod j,
se marcheaza in vectorul de componente incluziunea acestuia in componenta i. Se afiseaza
numarul de componente si vectorul viz este reintializat cu 0 pentru a fi utilizat la ulterioara
afisare. Daca nodul nu e vizitat si nu este depozit, acesta e afisat si este marcat cu 1 in
vectorul viz. Se parcurg restul nodurilor si se verifica daca fac parte din aceeasi componenta
tare conexa, caz in care se afiseaza si se marcheaza ca vizitate. 
	-- Functia recursive are ca parametrii graful g, un nod de inceput, vectorul viz si un 
parametru reverse ce indica daca parcurgerea se face in mod normal sau invers. Prima data 
se marcheaza nodul dat si apoi se parcurg toate celelalte noduri conform parametrului
reverse. Pentru fiecare dintre celalte noduri, se verifica daca acesta nu e vizitat, daca exista
arc catre el de la nodul dat, node, si daca nu este depozit, caz in care este reapelata 
functia reverse pentru acest nou, nod gasit. Astfel se realizeaza parcurgerea drumului si
se marcheaza cu 1 nodurile ce fac parte din componenta tare conexa curenta.

