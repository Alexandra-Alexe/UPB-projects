import java.util.*;

public abstract class Course {
     ArrayList<Student> students; //adaugat de mine
     ArrayList<Group> groups; //adaugat de mine
     String nameCourse;
     Teacher teacher;
     private Set assistants ;
     List<Grade> grades;
     HashMap<String, Group> dictionary; //cheie - id grupa; valoare - grupa
     int creditPoints;

    Course(CourseBuilder courseBuilder) {
        this.students = courseBuilder.students;
        this.groups = courseBuilder.groups;
        this.nameCourse = courseBuilder.nameCourse;
        this.teacher = courseBuilder.teacher;
        this.assistants = courseBuilder.assistants;
        this.grades = courseBuilder.grades;
        this.dictionary = courseBuilder.dictionary;
        this.creditPoints = courseBuilder.creditPoints;
    }

    //setteri
    public void setStudents(ArrayList<Student> students) {
        this.students = students;
    }

    public void setGroup(ArrayList<Group> groups) {
        this.groups = groups;
    }

    public void setTeacher(Teacher teacher) {
        this.teacher = teacher;
    }

    public void setAssistants(Set assistants) {
        this.assistants = assistants;
    }

    public void setListGrade(List<Grade> grades) {
        this.grades = grades;
    }

    public void setDictionar(String ID, Group group) {
        dictionary.put(ID, group);
    }

    public void setCreditPoints(int creditPoints) {
        this.creditPoints = creditPoints;
    }

    public void setNameCourse(String nameCourse) {
        this.nameCourse = nameCourse;
    }

    //getteri
    public ArrayList<Group> getGroup() {
        return groups;
    }

    public String getNameCourse() {
        return nameCourse;
    }

    public Teacher getTeacher() {
        return teacher;
    }

    public Set getAssistants() {
        return assistants;
    }

    public List<Grade> getListGrades() {
        return grades;
    }

    public Map<String, Group> getDictionary() {
        return dictionary;
    }

    public int getCreditPoints() {
        return creditPoints;
    }

    public String toString() {
        return nameCourse;
    }

    public void addAssistant(Assistant assistant, String ID) {
        if( assistants == null)
            assistants.add(assistant);

        for (Object i : assistants) {
            if (i.equals(assistant)) {
                break;
            }

            assistants.add(assistant);
        }

        Group group = new Group(ID, assistant);
        //seteaza asistentul in grupa cu id ul indicat
        for (String key : dictionary.keySet())
            if (key.equals(ID)) {
                group = dictionary.get(key); //dictionar(id grupei la care setez asistentul)
                break;
            }
        group.assistant = assistant;
        groups.add(group);
    }

    public void addStudent(String ID, Student student) {
        Group group;
        students.add(student);

        for (String key : dictionary.keySet())
            if (key.equals(ID)) {
                group = dictionary.get(key); //dictionar(id grupei la care adaug studentul)
                group.studentsGroup.add(student); // adaug studentul campul grupei sale
                group.addStudent(student);
                break;
            }
        //grupa pt cazul in care nu exista deja, se creeaza ulterior in main altfel,
        //studentul ramane neatribuit unei grupe
    }

    public void addGroup(Group group) {
        dictionary.put(group.ID, group);
    }

    public void addGroup(String ID, Assistant assistant) {
        Group group = new Group(ID, assistant);
        groups.add(group);
    }

    public void addGroup(String ID, Assistant assist, Comparator<Student> comp) {
        Group group = new Group(ID, assist, comp);
        groups.add(group);
    }

    public Grade getGrade(Student student) {
        for (Grade grade : grades)
            if (grade.getStudent().equals(student))
                return grade;
        return null;
    }

    public void addGrade(Grade grade) { //e bine?

        grades.add(grade);
        //AICI
    }

    public ArrayList<Student> getAllStudents() {
        for (Grade grade : grades)
            if (!students.contains(grade.getStudent()))
                students.add(grade.getStudent());
        return students;
    }

    public HashMap<Student, Grade> getAllStudentGrades() {
        HashMap<Student, Grade> StudentDictionary = new HashMap<>();
        for (Grade grade : grades)
            StudentDictionary.put(grade.getStudent(), grade);
        return StudentDictionary;
    }

    public abstract ArrayList<Student> getGraduatedStudents();

    Strategy strategy;

    public Student getBestStudent(String chosenStrategy) {
        if (chosenStrategy.equals("partial_score"))
            strategy = new BestPartialScore();
        if (chosenStrategy.equals("exam_score"))
            strategy = new BestExamScore();
        if (chosenStrategy.equals("total_score"))
            strategy = new BestTotalScoare();
        return strategy.BestGrade(this);
    }

    static abstract class CourseBuilder {
        private ArrayList<Student> students; //adaugat de mine
        private ArrayList<Group> groups; //adaugat de mine
        private String nameCourse;
        private Teacher teacher;
        private Set assistants;
        private List<Grade> grades;
        private HashMap<String, Group> dictionary; //cheie - id grupa; valoare - grupa
        private int creditPoints;
        public CourseBuilder(String nameCourse,Teacher teacher, Set assistants) {
            this.nameCourse = nameCourse;
            this.teacher = teacher;
            this.students = new ArrayList<>();
            this.groups = new ArrayList<>();
            this.assistants = new HashSet();
            this.assistants = assistants;
            this.grades = new ArrayList<>();
            this.dictionary = new HashMap<>();
        }

        public abstract ArrayList<Student> setStudents(ArrayList<Student> students);

        public abstract ArrayList<Group> setgroups(ArrayList<Group> groups);

        public abstract Teacher setTeacher(Teacher teacher) ;

        public abstract Set setAssistants(Set assistant) ;

        public abstract List<Grade> setListGrade(List<Grade> grade);

        public abstract HashMap<String, Group> setDictionar(HashMap<String, Group> dictionary);

        public abstract int setCreditPoints(int creditPoints) ;

        public abstract String setNameCourse(String nameCourse);

        public abstract Course courseBuilder();
    }
}

