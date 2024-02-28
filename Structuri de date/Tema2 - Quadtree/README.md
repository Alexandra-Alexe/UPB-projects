
Quadtree

Am implementat un algoritm de compresie și decompresie a imaginilor utilizând o structură de date numită "Quadtree". Algoritmul comprimă imaginile prin reprezentarea lor ca un arbore ierarhic, în care fiecare nod reprezintă o regiune a imaginii.

  - Imaginea de intrare este împărțită recursiv în sub-regiuni, iar media variației culorilor este calculată pentru fiecare regiune.
  - Dacă variația culorilor depășește un anumit factor dat, regiunea este divizată în patru sub-regiuni.
  - Procesul continuă până când fiecare regiune devine suficient de uniformă sau atinge o adâncime maximă.
  - Informațiile despre culori și structura arborelui sunt salvate într-un fișier binar.
  - Funcția cerinta1() implementează compresia imaginii folosind arborele Quadtree, iar funcția cerinta2() implementează decompresia imaginii.
