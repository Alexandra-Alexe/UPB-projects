import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Set;

public class FullCourse extends Course {

    FullCourse(CourseBuilder courseBuilder) {
        super(courseBuilder);
    }

    @Override
    public ArrayList<Student> getGraduatedStudents() {
        ArrayList<Student> graduatedStudents = new ArrayList<>();
        for( Grade grade : this.getListGrades())
            if(grade.getPartialScore() >= 3 && grade.getExamScore() >= 2)
                graduatedStudents.add(grade.getStudent());
        return graduatedStudents;
    }

    public static class FullCourseBuilder extends CourseBuilder {
        private ArrayList<Student> students; //adaugat de mine
        private ArrayList<Group> groups; //adaugat de mine
        private String nameCourse;
        private Teacher teacher;
        private Set assistants;
        private List<Grade> grades;
        private HashMap<String,Group> dictionary; //cheie - id grupa; valoare - grupa
        private int creditPoints;

        public FullCourseBuilder(String nameCourse, Teacher teacher, Set assistants1) {
            super(nameCourse,teacher,assistants1);
        }

        @Override
        public ArrayList<Student> setStudents(ArrayList<Student> students) {
            this.students = students;
            return students;
        }
        @Override
        public  ArrayList<Group> setgroups(ArrayList<Group> groups) {
            this.groups = groups;
            return groups;
        }
        @Override
        public  Teacher setTeacher(Teacher teacher) {
            this.teacher = teacher;
            return teacher;
        }
        @Override
        public Set setAssistants(Set assistant) {
            this.assistants = assistants;
            return assistants;
        }
        @Override
        public List<Grade> setListGrade(List<Grade> grade) {
            this.grades = grades;
            return grades;
        }
        @Override
        public HashMap<String,Group> setDictionar(HashMap<String,Group> dictionary ) {
            this.dictionary = dictionary;
            return dictionary;
        }
        @Override
        public  int setCreditPoints(int creditPoints) {
            this.creditPoints = creditPoints;
            return creditPoints;
        }
        @Override
        public  String setNameCourse(String nameCourse) {
            this.nameCourse = nameCourse;
            return nameCourse;
        }

        @Override
        public Course courseBuilder() {
            return new FullCourse(this);
        }

    }
}
