
                            ~ MN - Tema 1 ~

Algoritmul Iterative:
    Se deschide fisierul si se citeste in variabila N numarul de site-uri.
Initializez matricele A si M, de dimensiune NxN cu valoarea 0. Vectorul L este, de
asemenea initial nul. Acesta va retine numarul de linkuri detinut de fiecare site.
Este necesar un vector de dimnesiune N cu valori de 1. Varibilele v_curr si
v_prev vor reprezenta vectorul curent si vectorul precendet, utilizati pentru 
a afla vectorul final, PR. Matricea A este matricea aditionala in care sunt     
marcate legaturile dintre site-uri. Se citesc valorile de pe fiecare linie din
fisier in vectorul aux si se completeaza corespunzator cate o linie din matricea 
A si cate o valoare din vectorul L. In urmatoarea parcurgere, se marcheaza cu 0
in matricea de adiacenta site-urile care se autoapeleaza si este decremnetat    
numarul de linkuri din vector. Conform formulei, este creata matricea M. Vectorul
precendent ia valorile celui curent, iar cel din urma este recalculat conform 
formulei pana cand diferenta dintre valorile acestora este mai mica decat eroarea 
data. In final, vectorul ce retine indicii Page Rank este ultimul v_prev calculat.

