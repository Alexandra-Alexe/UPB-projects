
public class Grade implements Comparable, Cloneable{
    private Double partialScore, examScore;
    private Student student;
    private String course;
    Grade (Double partialScore, Double examScore, Student student, String course) {
        this.partialScore = partialScore;
        this.examScore = examScore;
        this.student = student;
        this.course = course;
    }

    Double getPartialScore() {
        return partialScore;
    }
    Double getExamScore() {
        return examScore;
    }
    Student getStudent() {
        return student;
    }
    String getCourse() {
        return course;
    }

    void setPartialScore(Double partialScore) {
        this.partialScore = partialScore;
    }
    void setExamScore(Double examScore) {
        this.examScore = examScore;
    }
    void setStudent(Student student) {
        this.student = student;
    }
    void setCourse(String course) {
        this.course = course;
    }
    public Double getTotal() {
        return partialScore + examScore;
    }

    @Override
    public int compareTo(Object o) {
        if(this.getTotal() < ((Grade)o).getTotal())
            return -1;
        else if(this.getTotal() > ((Grade)o).getTotal() )
            return 1;
        return 0;
    }
    public String toString() {
        return "partial: " + partialScore + " examen: " + examScore + "\n";
    }
}
