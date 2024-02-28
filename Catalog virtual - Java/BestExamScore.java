public class BestExamScore implements Strategy{

    @Override
    public Student BestGrade(Course course) {
        Double bestExamScore = 0.0;
        Grade bestExamGrade = null;
        for( Grade grade : course.getListGrades())
            if(grade.getExamScore() > bestExamScore ) {
                bestExamGrade = grade;
                bestExamScore = grade.getExamScore();
            }
        return bestExamGrade.getStudent();
    }
}
 
