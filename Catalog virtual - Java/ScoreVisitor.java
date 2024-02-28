import java.util.ArrayList;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;

public class ScoreVisitor implements Visitor{
      public HashMap<Teacher,List<Tuple>> examScores;
      public HashMap<Assistant,List<Tuple>> partialScores;
      Catalog catalog = Catalog.getInstance();

      ScoreVisitor () {
          examScores = new HashMap<>();
          partialScores = new HashMap<>();
      }
    public void addExamScore(Teacher teacher, Course course,Grade grade) {
        Tuple<Student,String,Grade> tuple = new Tuple<>(grade.getStudent(),course.getNameCourse(),grade);
        examScores.put(teacher, Collections.singletonList(tuple));
        catalog.notifyObservers(grade);
    }
    public void addPartialScore(Course course, Grade grade, ArrayList<Group> groups) {
        Tuple<Student,String,Grade> tuple = new Tuple<>(grade.getStudent(),course.getNameCourse(),grade);
        for( Group group : groups)
                if(group.studentsGroup.contains(grade.getStudent())) {
                    partialScores.put(group.assistant, Collections.singletonList(tuple));
                    //catalog.notifyObservers(grade);
                    break;
                }
    }

    @Override
    public void visit(Teacher teacher) {
         // addExamScore(teacher,((Grade)examScores.get(teacher)).getCourse(),((examScores.get(teacher)));
        for(Tuple tuple : examScores.get(teacher)) {
            for(Course course : catalog.listCourses) {
                if( course.equals(tuple.getCourseName())) {
                    for(Grade grade : course.getListGrades()) {
                        if(grade.getStudent().equals(tuple.getStudent())) {
                            grade.setExamScore(((Grade) tuple.getGrade()).getExamScore());
                            catalog.notifyObservers(grade);
                        }
                    }
                }
            }
        }
    }

    @Override
    public void visit(Assistant assistant) {
          for(Tuple tuple : partialScores.get(assistant)) {
              for(Course course : catalog.listCourses) {
                  if(course.equals(tuple.getCourseName())) {
                      for( Grade grade : course.getListGrades()) {
                          if( grade.getStudent().equals(tuple.getStudent())) {
                              grade.setPartialScore(((Grade) tuple.getGrade()).getPartialScore());
                              catalog.notifyObservers(grade);
                          }
                      }
                  }
              }
          }
    }

    public String toString() {
        return examScores + " +  " + partialScores;
    }

    private static class Tuple<S,C,G> {
        S student;
        C courseName;
        G grade;
        Tuple(S student,C courseName, G grade) {
            this.student = student;
            this.courseName = courseName;
            this.grade = grade;
        }
        public S getStudent() {
            return student;
        }

        public G getGrade() {
            return grade;
        }

        public C getCourseName() {
            return courseName;
        }
    }
}
