Tema - POO

Acest proiect reprezintă implementarea unui catalog virtual în limbajul de programare Java. Catalogul virtual permite gestionarea cursurilor, grupelor, studenților și a altor entități asociate. Proiectul este organizat în mai multe fișiere, fiecare având rolul său specific în funcționarea catalogului virtual. 

Main.java
Fișierul Main.java defineste obiectele și creeaza instanțele necesare pentru funcționarea catalogului. De asemenea, se realizează operațiile de gestionare a datelor, cum ar fi adăugarea și ștergerea cursurilor, afișarea informațiilor despre studenți și evaluări, și gestionarea asistenților și profesorilor.

Catalog.java
Fișierul Catalog.java conține clasa Catalog, care reprezintă catalogul virtual propriu-zis. Această clasă gestionează cursurile, oferind funcționalități pentru adăugarea și ștergerea acestora, precum și pentru afișarea informațiilor relevante. De asemenea, implementează un mecanism de observare pentru notificarea părinților cu privire la rezultatele studenților lor. Această funcționalitate permite interogarea informațiilor despre studenți și evaluări, consolidând rolul său în coordonarea și administrarea procesului educațional.

Course.java
Fișierul Course.java conține clasa Course, care definește un curs în cadrul catalogului virtual. Această clasă gestionează informațiile legate de curs, inclusiv grupurile asociate, asistenții și profesorul care predă cursul, precum și evaluările și datele legate de studenți. Oferă funcționalități pentru adăugarea și ștergerea de asistenți și studenți, precum și pentru obținerea informațiilor despre studenți și evaluări. De asemenea, implementează un mecanism pentru determinarea celor mai buni studenți în funcție de strategiile specificate.

Observer.java
Fișierul Observer.java conține interfața Observer, care definește metoda update(Notification notification) utilizată de observatorii care urmăresc anumite evenimente în catalogul virtual. Această interfață oferă un mecanism pentru notificarea observatorilor atunci când apar modificări în sistemul catalogului virtual.

Subject.java
Fișierul Subject.java conține interfața Subject, care definește metodele pentru subiecții care pot fi observați în cadrul catalogului virtual.

Notification.java
Fișierul Notification.java conține clasa Notification, care reprezintă o notificare trimisă către observatori în cazul unor evenimente specifice în catalogul virtual.

Funcționalități cheie

Gestionarea cursurilor: Adăugare, ștergere și afișare a cursurilor din catalog.
Gestionarea grupelor și a studenților: Adăugare, ștergere și afișare a grupurilor de studenți și a detaliilor despre aceștia.
Gestionarea evaluărilor: Înregistrarea și afișarea notelor obținute de către studenți la diferitele cursuri.
Gestionarea personalului didactic: Adăugarea și gestionarea profesorilor și a asistenților asociate cursurilor.
Utilizare

Pentru a utiliza catalogul virtual, este necesară rularea fișierului Main.java, care conține funcția principală a proiectului. Aici sunt create și gestionate toate obiectele și operațiile necesare pentru funcționarea catalogului.
