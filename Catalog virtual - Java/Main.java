import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class Main {
    public static void main(String[] args) {
        Catalog catalog = Catalog.getInstance();
        ScoreVisitor visitor = new ScoreVisitor();
        visitor.catalog = catalog;
        UserFactory userFactory = new UserFactory();

        //GRUPA1
        User student1 = userFactory.getUser("Student","Gigel", "Frone");
        User mother1 = userFactory.getUser("Parent","Maria","Frone");
        User father1 = userFactory.getUser("Parent","Daniel","Frone");
        ((Student)student1).setMother((Parent) mother1);
        ((Student)student1).setFather((Parent) father1);
        User student2 = userFactory.getUser("Student","Cosmin", "Andrei");
        User father2 = userFactory.getUser("Parent","Vasile","Andrei");
        ((Student)student2).setFather((Parent) father2);
        User student3 = userFactory.getUser("Student","Ionel", "Dragomir");
        User mother2 = userFactory.getUser("Parent","Letitia","Dragomir");
        ((Student)student3).setMother((Parent) mother2);
        User student4 = userFactory.getUser("Student","Florin", "Florea");
        User mother3 = userFactory.getUser("Parent","Adriana","Florea");
        User father3 = userFactory.getUser("Parent","Catalin","Florea");
        ((Student)student4).setMother((Parent) mother3);
        ((Student)student4).setFather((Parent) father3);
        User student5 = userFactory.getUser("Student","Costel", "Busuioc");
        User mother4 = userFactory.getUser("Parent","Carmen","Busuioc");
        User father4 = userFactory.getUser("Parent","Nelu","Busuioc");
        ((Student)student5).setMother((Parent) mother4);
        ((Student)student5).setFather((Parent) father4);
        Assistant assistant1 = new Assistant("Andrei","Georgescu");
        Group group1 = new Group("312CC", assistant1);


        //GRUPA2
        User student6 = userFactory.getUser("Student","Sebastian", "Moisescu");
        User mother5 = userFactory.getUser("Parent","Viorela","Moisescu");
        User father5 = userFactory.getUser("Parent","Ionut","Moisescu");
        ((Student)student6).setMother((Parent) mother5);
        ((Student)student6).setFather((Parent) father5);
        User student7 = userFactory.getUser("Student","Larisa", "Oana");
        User father6 = userFactory.getUser("Parent","Alecu","Oana");
        ((Student)student7).setFather((Parent) father6);
        User student8 = userFactory.getUser("Student","Georgiana", "Calin");
        User mother6 = userFactory.getUser("Parent","Lidia","Calin");
        ((Student)student8).setMother((Parent) mother6);
        User student9 = userFactory.getUser("Student","Dragos", "Barbu");
        User mother7 = userFactory.getUser("Parent","Anastasia","Barbu");
        User father7 = userFactory.getUser("Parent","Lucian","Barbu");
        ((Student)student9).setMother((Parent) mother7);
        ((Student)student9).setFather((Parent) father7);
        User student10 = userFactory.getUser("Student","Alberto", "Ciobanu");
        User mother8 = userFactory.getUser("Parent","Mihaela","Ciobanu");
        User father8 = userFactory.getUser("Parent","Emil","Ciobanu");
        ((Student)student10).setMother((Parent) mother8);
        ((Student)student10).setFather((Parent) father8);
        Assistant assistant2 = new Assistant("Alexandra","Maria");
        Group group2 = new Group("314CC", assistant2);

        Teacher teacher1 = new Teacher("Ion","Mihalache");
        Set assistants1 = new HashSet<>();
        assistants1.add(assistant1);
        assistants1.add(assistant2);
        Course curs1 =  new FullCourse(new FullCourse.FullCourseBuilder("Programare orientata pe obiecte",teacher1,assistants1));
        curs1.addGroup(group1);
        curs1.addGroup(group2);
        curs1.setTeacher(teacher1);


        curs1.addStudent("312CC",(Student) student1);
        curs1.addStudent("312CC",(Student) student2);
        curs1.addStudent("312CC",(Student) student3);
        curs1.addStudent("312CC",(Student) student4);
        curs1.addStudent("312CC",(Student) student5);
        curs1.addStudent("314CC",(Student) student6);
        curs1.addStudent("314CC",(Student) student7);
        curs1.addStudent("314CC",(Student) student8);
        curs1.addStudent("314CC",(Student) student9);
        curs1.addStudent("314CC",(Student) student10);


        //GRUPA3
        User student11 = userFactory.getUser("Student","Livia", "Ursu");
        User student12 = userFactory.getUser("Student","Alfred", "Pop");
        User father9 = userFactory.getUser("Parent","Albert","Pop");
        ((Student)student12).setFather((Parent) father9);
        User student13 = userFactory.getUser("Student","Iulian", "Iancu");
        User mother9 = userFactory.getUser("Parent","Elena","Iancu");
        ((Student)student13).setMother((Parent) mother9);
        User student14 = userFactory.getUser("Student","Sofia", "Negoita");
        User mother10 = userFactory.getUser("Parent","Ana","Negoita");
        User father10 = userFactory.getUser("Parent","Marius","Negoita");
        ((Student)student14).setMother((Parent) mother10);
        ((Student)student14).setFather((Parent) father10);
        User student15 = userFactory.getUser("Student","Alma", "Dobrica");
        User mother11 = userFactory.getUser("Parent","Corina","Dobrica");
        User father11 = userFactory.getUser("Parent","Cristi","Dobrica");
        ((Student)student15).setMother((Parent) mother11);
        ((Student)student15).setFather((Parent) father11);
        Assistant assistant3 = new Assistant("Adrian","Sava");
        Group group3 = new Group("311CC", assistant3);


        //GRUPA4
        User student16 = userFactory.getUser("Student","Cristian", "Manole");
        User mother12 = userFactory.getUser("Parent","Victoria","Manole");
        User father12 = userFactory.getUser("Parent","Andrei","Manole");
        ((Student)student16).setMother((Parent) mother12);
        ((Student)student16).setFather((Parent) father12);
        User student17 = userFactory.getUser("Student","Denisa", "Pavel");
        User father13 = userFactory.getUser("Parent","Bogdan","Pavel");
        ((Student)student17).setFather((Parent) father13);
        User student18 = userFactory.getUser("Student","Alex", "Petrescu");
        User mother13 = userFactory.getUser("Parent","Monica","Petrescu");
        ((Student)student18).setMother((Parent) mother13);
        User student19 = userFactory.getUser("Student","Cosmin", "Tomulescu");
        User student20 = userFactory.getUser("Student","Camelia", "Tunaru");
        User mother14 = userFactory.getUser("Parent","Petra","Tunaru");
        User father14 = userFactory.getUser("Parent","Cristian","Tunaru");
        ((Student)student20).setMother((Parent) mother14);
        ((Student)student20).setFather((Parent) father14);
        Assistant assistant4 = new Assistant("Emilian","Voinea");
        Group group4 = new Group("313CC", assistant4);

        Teacher teacher2 = new Teacher("George","Dinu");
        Set assistants2 = new HashSet<>();
        assistants2.add(assistant3);
        assistants2.add(assistant4);
        Course curs2 =  new PartialCourse(new PartialCourse.PartialCourseBuilder("Electronica digitala",teacher2, assistants2));
        curs2.addAssistant(assistant3,"311CC");
        curs2.addAssistant(assistant4,"313CC");
        curs2.setTeacher(teacher2);

        curs2.addStudent("311CC",(Student) student11);
        curs2.addStudent("311CC",(Student) student12);
        curs2.addStudent("311CC",(Student) student13);
        curs2.addStudent("311CC",(Student) student14);
        curs2.addStudent("311CC",(Student) student15);
        curs2.addStudent("313CC",(Student) student16);
        curs2.addStudent("313CC",(Student) student17);
        curs2.addStudent("313CC",(Student) student18);
        curs2.addStudent("313CC",(Student) student19);
        curs2.addStudent("313CC",(Student) student20);

        Grade grade1 = new Grade(2.3,4.5,(Student) student1, curs1.getNameCourse());
        Grade grade2 = new Grade(3.4,2.7,(Student) student2, curs1.getNameCourse());
        Grade grade3 = new Grade(4.5,2.6,(Student) student3, curs1.getNameCourse());
        Grade grade4 = new Grade(4.6,3.4,(Student) student4, curs1.getNameCourse());
        Grade grade5 = new Grade(1.7,4.2,(Student) student5, curs1.getNameCourse());
        Grade grade6 = new Grade(3.8,4.6,(Student) student6, curs1.getNameCourse());
        Grade grade7 = new Grade(2.9,1.7,(Student) student7, curs1.getNameCourse());
        Grade grade8 = new Grade(4.1,2.8,(Student) student8, curs1.getNameCourse());
        Grade grade9 = new Grade(1.2,3.9,(Student) student9, curs1.getNameCourse());
        Grade grade10 = new Grade(2.3,1.5,(Student) student10, curs1.getNameCourse());
        Grade grade11 = new Grade(1.3,4.2,(Student) student11, curs2.getNameCourse());
        Grade grade12 = new Grade(3.3,4.7,(Student) student12, curs2.getNameCourse());
        Grade grade13 = new Grade(4.5,1.9,(Student) student13, curs2.getNameCourse());
        Grade grade14 = new Grade(1.6,4.0,(Student) student14, curs2.getNameCourse());
        Grade grade15 = new Grade(1.2,2.2,(Student) student15, curs2.getNameCourse());
        Grade grade16 = new Grade(6.8,4.6,(Student) student16, curs2.getNameCourse());
        Grade grade17 = new Grade(2.7,3.7,(Student) student17, curs2.getNameCourse());
        Grade grade18 = new Grade(4.9,2.2,(Student) student18, curs2.getNameCourse());
        Grade grade19 = new Grade(4.4,4.9,(Student) student19, curs2.getNameCourse());
        Grade grade20 = new Grade(4.3,1.2,(Student) student20, curs2.getNameCourse());

        visitor.addExamScore(teacher1, curs1, grade1);
        visitor.addExamScore(teacher1, curs1, grade2);
        visitor.addExamScore(teacher1, curs1, grade3);
        visitor.addExamScore(teacher1, curs1, grade4);
        visitor.addExamScore(teacher1, curs1, grade5);
        visitor.addExamScore(teacher1, curs1, grade6);
        visitor.addExamScore(teacher1, curs1, grade7);
        visitor.addExamScore(teacher1, curs1, grade8);
        visitor.addExamScore(teacher1, curs1, grade9);
        visitor.addExamScore(teacher1, curs1, grade10);
        visitor.addExamScore(teacher2, curs2, grade11);
        visitor.addExamScore(teacher2, curs2, grade12);
        visitor.addExamScore(teacher2, curs2, grade13);
        visitor.addExamScore(teacher2, curs2, grade14);
        visitor.addExamScore(teacher2, curs2, grade15);
        visitor.addExamScore(teacher2, curs2, grade16);
        visitor.addExamScore(teacher2, curs2, grade17);
        visitor.addExamScore(teacher2, curs2, grade18);
        visitor.addExamScore(teacher2, curs2, grade19);
        visitor.addExamScore(teacher2, curs2, grade20);


        ArrayList<Group> arrayListGroupsCourse1 =  new ArrayList<>();
        arrayListGroupsCourse1.add(group1);
        arrayListGroupsCourse1.add(group2);
        ArrayList<Group> arrayListGroupsCourse2 =  new ArrayList<>();
        arrayListGroupsCourse2.add(group3);
        arrayListGroupsCourse2.add(group4);


        visitor.addPartialScore(curs1, grade1,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade2,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade3,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade4,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade5,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade6,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade7,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade8,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade9,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade10,arrayListGroupsCourse1 );
        visitor.addPartialScore(curs1, grade11,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade12,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade13,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade14,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade15,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade16,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade17,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade18,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade19,arrayListGroupsCourse2 );
        visitor.addPartialScore(curs1, grade20,arrayListGroupsCourse2 );


        catalog.addCourse(curs1);
        catalog.addCourse(curs2);

        //functionalitatea metodelor din catalog
        System.out.println("Catalogul " + catalog.name + " contine urmatorele cursuri: ");
        catalog.showCourses();
        curs1.setNameCourse("Programare orientata pe obiecte");
        System.out.println("Dupa redenumire, cursurile existente sunt: ");
        catalog.showCourses();
        System.out.println("Se sterge pt exemplificare cursul 'Programare orientata pe obiecte' si se afiseaza catalogul din nou:");
        catalog.removeCourse(curs1);
        catalog.showCourses();
        catalog.addCourse(curs1);
        System.out.println();


        System.out.println("Asistentii cursului " + curs2.getNameCourse() + " sunt: " + curs2.getAssistants());
        System.out.println("Asistentii cursului " + curs1.getNameCourse() + " sunt: " + curs1.getAssistants() );
        System.out.println();


        System.out.println("Grupele retinute in dictionar sunt: " + curs1.getDictionary());
        System.out.println("Studentii din " + group3.ID + ": " + group3.studentsGroup);
        System.out.println();


        System.out.println("Notelor studentilor cursului " + curs1.getNameCourse() + " sunt:"); //functionalitatea metodei getAllStudentsGrade
        System.out.println(curs1.getAllStudentGrades());

        System.out.println("Studentii cursului " + curs1.getNameCourse() + curs1.getAllStudents());
        System.out.println("Studentii promovati ai cursului 1: " + curs1.getGraduatedStudents()); //functionalitate metoda getGraduatedStudents
        System.out.println();

        System.out.println("Cel mai bun student al cursului " + curs1.getNameCourse() + " - punctaj in timpul semestrului");
        System.out.println(curs1.getBestStudent("partial_score"));
        System.out.println("Cel mai bun student al cursului " + curs1.getNameCourse() + " - punctaj in examen");
        System.out.println(curs1.getBestStudent("exam_score"));
        System.out.println("Cel mai bun student al cursului " + curs1.getNameCourse() + " - punctaj total");
        System.out.println(curs1.getBestStudent("total_score"));
        System.out.println();


        //functionalitate Visitor si Observer
        for( Course course : catalog.listCourses) {
            for( Student student : course.getAllStudents()) {
                if(student.getFather() != null)
                    (student.getFather()).setCatalog(catalog);
                if(student.getMother() != null)
                    (student.getMother()).setCatalog(catalog);
            }
            course.getTeacher().accept(visitor);
            for( Object assistant : course.getAssistants())
                ((Assistant)assistant).accept(visitor);
        }
    }
}

