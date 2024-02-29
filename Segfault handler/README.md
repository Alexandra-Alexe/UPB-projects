# TEMA 1 - Sisteme de operare

In cadrul acestei teme, am implementat functia segv_handler prin care se realizeaza maparea in cazul unui acces permis 
si valid la memorie. Am abordat acesta problema folosind o matrice pentru a cunoaste ce pagini au fost mapate si am considerat 
3 cazuri de pozitionare a paginii in cadrul fisierului. Consider ca tema acesta a fost utila deoarece am inteles mult mai bine 
felul in care executabilele sunt incarcate si rulate, dar timpul petrecut pentru a cauta informatii, legate de conceptele 
teoretice, nu a fost nesemnificativ. Cred ca implementarea mea este una acceptabila, dar exista variante mai eficiente.


In primul rand se identifica din care segment face parte adresa de page fault si se retine indexul acestuia in index_seg, 
altfel acesta retine valoarea initiala -1.  Daca a fost gasit segmentul, aflarea paginii, page, se face utilizand adresa de 
page fault, adresa de inceput a segmentului si dimensiunea paginii. Cateva informatii din campurile structurii se retin in
variabilele mem_size, file_size, offset_mapping si addr_mapping pentru o intelegere si parcurgere mai usoara a codului. In 
variabilele offset_mapping si addr_mapping se calculeaza exact offsetul si adresa la care va avea loc maparea. In cazul in
care nu a fost gasit un segment sau in cazul in care pagina a fost deja mapata, fapt ce se verifica cu ajutorul matricei a, 
atunci handler-ul genereaza eroarea segmentation fault. Altfel, maparea are loc in functie de pozitia paginii in fisier.
Varibilele beginning_of_page_size si end_of_page_size se refera la dimensiunea paginilor pana la inceputul celei ce trebuie 
mapate, respectiv dimensiunea paginilor de la inceput pana la cea ce va fi mapata, inclusiv. 
 - In cazul in care pagina nu se afla in totalitate in fisier, alaturi de mapare se zerorieaza zona din afara, zona bss. 
 Stiind ca maparea se realizeaza pe o pagina, se tine cont si de dimensiunea maxima a segmentului in memorie. 
 - In cazul in care pagina se afla in intregime in fisier, se mapeaza la adresa exacta folosind permisiunile segmentului. 
 Fiecare mapare este verificare folosind macro-ul DIE si ulterior se marcheaza in matricea a acest lucru. 
 - Daca pagina se afla in afara fisierului, se mapeaza si se pune 0 folosind mmap, ce are activat flag-ul MAP_ANONYMOUS pentru 
 acest lucru.
