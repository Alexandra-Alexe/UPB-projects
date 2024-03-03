 Tema - POO

Acest proiect reprezintă implementarea unui catalog virtual în limbajul de programare Java. Catalogul virtual permite gestionarea cursurilor, grupelor, studenților și a altor entități asociate. Proiectul este organizat în mai multe fișiere, fiecare având rolul său specific în funcționarea catalogului virtual. 

 Main.java

Fișierul Main.java defineste obiectele și creeaza instanțele necesare pentru funcționarea catalogului. De asemenea, se realizează operațiile de gestionare a datelor, cum ar fi adăugarea și ștergerea cursurilor, afișarea informațiilor despre studenți și evaluări, și gestionarea asistenților și profesorilor.

 BestExamScore.java, BestPartialScore.java, BestTotalScore.java

Cele trei fișiere definesc trei clase distincte care implementează interfața Strategy. Aceste clase reprezintă strategii diferite pentru a determina cel mai bun student în cadrul unui curs, în funcție de scorul obținut în examen, scorul parțial sau scorul total. Fiecare clasă implementează metoda BestGrade(Course course) a interfeței Strategy, care iterează prin lista de note dintr-un curs dat și determină cea mai înaltă notă conform strategiei respective. Deși structura codului este similară în cele trei clase, logica din spate variază în funcție de tipul de scor considerat. 

Catalog.java

Fișierul Catalog.java conține clasa Catalog, care reprezintă catalogul virtual propriu-zis. Această clasă gestionează cursurile, oferind funcționalități pentru adăugarea și ștergerea acestora, precum și pentru afișarea informațiilor relevante. De asemenea, implementează un mecanism de observare pentru notificarea părinților cu privire la rezultatele studenților lor. Această funcționalitate permite interogarea informațiilor despre studenți și evaluări, consolidând rolul său în coordonarea și administrarea procesului educațional.

Course.java

Fișierul Course.java conține clasa Course, care definește un curs în cadrul catalogului virtual. Această clasă gestionează informațiile legate de curs, inclusiv grupurile asociate, asistenții și profesorul care predă cursul, precum și evaluările și datele legate de studenți. Oferă funcționalități pentru adăugarea și ștergerea de asistenți și studenți, precum și pentru obținerea informațiilor despre studenți și evaluări. De asemenea, implementează un mecanism pentru determinarea celor mai buni studenți în funcție de strategiile specificate.

Element.java

Interfața Element definește o metodă accept(Visitor visitor) pentru obiectele care pot fi vizitate de un Visitor. Aceasta face parte din design pattern-ul "Visitor", permițând separarea operațiilor sau algoritmilor de structura obiectelor pe care le aplică. Prin intermediul acestei interfețe, obiectele pot primi vizitatori și pot permite acestora să efectueze operații specifice în funcție de tipul și starea obiectului, promovând astfel un design flexibil și modular al aplicației.

FullCourse.java

Clasa FullCourse extinde clasa abstractă Course și implementează logica specifică unui curs complet. Ea determină studenții absolvenți pe baza notelor lor parțiale și de examen. Clasa conține un FullCourseBuilder intern care facilitează construirea obiectelor de tip FullCourse, permitând setarea detaliilor necesare, cum ar fi studenții, grupurile, profesorul, asistenții, notele și punctele de credit.

Grade.java

Clasa Grade definește structura unei note pentru un student în cadrul unui curs. Aceasta conține informații despre nota parțială, nota de examen, studentul și cursul asociat. Metodele din clasa permit accesul și setarea acestor detalii, inclusiv calculul notei totale ca sumă a notei parțiale și a celei de examen. Implementarea interfeței Comparable permite compararea obiectelor Grade în funcție de nota totală. Clasa oferă, de asemenea, o metodă de afișare pentru a prezenta detaliile notei.

Group.java

Clasa Group definește o grupă în cadrul catalogului virtual, reprezentată printr-o colecție ordonată de studenți într-un obiect de tip TreeSet. Această clasă gestionează informații despre studenții din grupă, asistentul care îi coordonează și un identificator unic al grupei. Metodele permit adăugarea de studenți în grupă și oferă funcționalități de inițializare și afișare a detaliilor despre grupă.

Notification.java

Fișierul Notification.java conține clasa Notification, care reprezintă o notificare trimisă către observatori în cazul unor evenimente specifice în catalogul virtual. Această clasă conține un câmp pentru o notă și un constructor care primește și atribuie această notă. În plus, supraîncărcarea metodei toString() permite generarea unei reprezentări textuale a obiectului Notification.

Observer.java

Fișierul Observer.java conține interfața Observer, care definește metoda update(Notification notification) utilizată de observatorii care urmăresc anumite evenimente în catalogul virtual. Această interfață oferă un mecanism pentru notificarea observatorilor atunci când apar modificări în sistemul catalogului virtual.

PartialCourse.java

Clasa PartialCourse reprezintă un curs parțial în cadrul catalogului virtual, extinzând funcționalitatea clasei Course. Metoda sa getGraduatedStudents() determină lista absolvenților cursului parțial pe baza notelor obținute, adăugând studenții cu o notă totală de cel puțin 5. Clasa internă PartialCourseBuilder facilitează construirea obiectelor PartialCourse, primind informații necesare precum numele cursului, profesorul, asistenții și altele, și oferind metode pentru setarea și returnarea acestor parametri.

ScoreVisitor.java

Clasa ScoreVisitor reprezintă un vizitator care colectează și gestionează notele obținute în cadrul cursurilor din catalogul virtual. Acesta utilizează două hashmaps, examScores și partialScores, pentru a stoca notele examenelor și parțiale, asociate cu profesorii și asistenții corespunzători. Metoda addExamScore adaugă note de examen pentru un profesor și un curs specific, în timp ce addPartialScore înregistrează notele parțiale pentru un anumit curs și grupuri de studenți. Implementând interfața Visitor, clasa vizitează profesorii și asistenții, actualizând notele în funcție de tipul de observator. Metoda toString furnizează o reprezentare text a notelor. De asemenea, clasa include o clasă internă Tuple, utilizată pentru a stoca informațiile relevante despre note și cursuri.

Strategy.java

Interfața Strategy definește un șablon pentru strategiile de evaluare a scorurilor din cadrul cursurilor. Metoda BestGrade este responsabilă pentru determinarea și returnarea celui mai bun student în funcție de o anumită strategie specificată. Folosind această interfață, alte clase implementeaza logica de evaluare a notelor conform propriilor criterii.

Subject.java

Fișierul Subject.java conține interfața Subject, care definește metodele pentru subiecții care pot fi observați în cadrul catalogului virtual. Aceste metode includ addObserver(Observer observer), utilizată pentru adăugarea unui observator, removeObserver(Observer observer) pentru eliminarea unui observator și notifyObservers(Grade grade) pentru notificarea observatorilor cu privire la un anumit eveniment, în acest caz, o notă. Această interfață facilitează implementarea modelului Observer în sistemul de gestionare a catalogului virtual.

User.java

Clasa User este o clasă abstractă care servește drept model de bază pentru utilizatori. Aceasta conține atributele firstName și lastName pentru numele utilizatorului și o metodă de afișare a numelui complet. Clasa Student extinde clasa User și implementează interfața Comparable pentru a permite comparația între obiecte de tip student pe baza numelui de familie. Clasa Parent reprezintă un părinte și implementează interfața Observer pentru a putea fi notificat despre anumite evenimente din cadrul catalogului. Clasa Teacher reprezintă un profesor și implementează interfața Element pentru a putea fi vizitată de un vizitator extern. Clasa Assistant reprezintă un asistent și, similar cu clasa Teacher, implementează interfața Element. UserFactory returnează instanțe de utilizatori pe baza tipului specificat. Această structură permite crearea și gestionarea diferitelor tipuri de utilizatori în cadrul sistemului.

Visitor.java

Interfața Visitor definește metodele necesare pentru a vizita diferite tipuri de obiecte într-o structură de obiecte. Metodele visit(Assistant assistant) și visit(Teacher teacher) permit vizitatorului să efectueze acțiuni specifice pe asistenți și profesori atunci când acestea sunt vizitate în cadrul unei structuri de obiecte.
