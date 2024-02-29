# Tema 2

# MyDispatcher

In functia addTask, am setat in primul rand volumul de munca al unui task ca
    fiind durata sa. Am adaugat in antetul functiei addTask cuvantul cheie syncronized
    pentru a asigura accesul sigur si coerent la resursele partajate. Apoi am implementat
    fiecare politica in parte: 
- pentru Round Robin, task-urile sunt alocate pe masura ce vin. Ma folosesc de 
    variabila id, care initial este 0, pentru a calcula host care trebuie sa se ocupa 
    de acel task.
- in cazul politicii Shortest Queue, parcurg toate host-urile existente si retin in 
    varibaila min valoarea celei mai scurte cozi si in variabila index, pozitia host-ului.
    In cazul a doua cozi cu dimensiune egale, se va considera cea cu id-ului mai mic. Apoi
     se adauga task-ul in coada host-ului respectiv, apelandu-se functia addTask din MyHost.
- in cazul politicii Size Interval Task Assignment, se verifica campul type al task-ului
     si in functie de acesta se face adaugarea in coada unuia dintre cele 3 host-uri.
- pentru politica Least Work Left, am procedat in mod asemanator ca la politica SQ, de 
    data aceasta folosindu-ma de metoda getWorkLeft().Am cautat host-ul cu cel mai mic volum 
    de munca, i-am retinut pozitia in variabila index si am apelat metoda de adaugarea a 
    task-ului.

# MyHost

- In functia run, se ruleaza thread-ul curent pana cand este intrerupt. In primul rand 
    vreau sa scot task-ul cu prioritate maxima din coada, asa ca folosind un interator parcurg
     toate coada si marchez succesul prin flag1. Deci daca flag1 are valoarea 1, pun variabila 
     task, task-ul gasit si il sterg din coada pentru ca urmeaza sa il execut. In variabila 
     task se va afla mereu task-ul care ruleaza in momentul prezent de timp sau task-ul care a
      rulat inainte. In cazul in care nu a fost gasit un task cu prioritate ca primul, scot in
       variabila task primul element din coada.
- Daca in task, exista un task valid care mai are secunde de rulat, vrem sa incepem executia.
     Ma asigur ca e momentul de timp pentru ca acel task de inceapa, verificand prin metoda 
     getStart. Altfel astept cat este necesar. Apoi execut task-ul cat timp mai are secunde ramase
      si cat timp nu devine preemptat. Daca este preemptabil, verific aparitia unui task mai 
      prioritar. Parcurg toate coada si daca se gaseste un task cu prioritate mai mare, marchez acest
       lucru prin variabila flag2. Daca valoarea variabilei flag2 devine 1, task-ul curent este 
       adaugat inapoi in coada, fiind neterminat si rularea respectiva este oprita. Altfel, task-ul 
       curent sta in sleep cate o secunda, dupa care iar se face verificarea pt a vedea daca trebuie 
       preemptat si tot asa. La final, cand un task nu mai are nicio secunda de rulat, apelez metoda
        finish() pe el, si modific variabila executingTask in 0 pentru ca in acel moment nu mai 
        ruleaza niciun task. M-am asigurat printr-un bloc syncronized, ce curinde astepatarea 
        momentului de start si rularea propriu-zisa, ca nu ajunge la race condition uri.
- In functia addTask, task-ul primit este adaugat in coada host-ului.
- Functia getQueueSize returneaza dimensiunea cozii, adunand 1 (sau nu) pentru situatia in care 
    exista un task care ruleaza in acel moment (sau nu).
- Functia getWorkLeft parcurge toate task-urile din coada si aduna in variabila work_left duratele
     acestora. Daca in acel moment exista un task in desfasurare, se aduna si secundele sale ramase. 
    Valoarea este rotunjita la secunde si este returnata.
- Functia shutdown, apeleaza intreruperea threadului. 
