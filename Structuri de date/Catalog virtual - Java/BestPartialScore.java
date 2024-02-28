import java.util.ArrayList;

public class BestPartialScore implements Strategy {
    @Override
    public Student BestGrade(Course course) {
        Double bestPartialScore = 0.0;
        Grade bestPartialGrade = null;
        for( Grade grade : course.getListGrades())
            if(grade.getPartialScore() > bestPartialScore ) {
                bestPartialGrade = grade;
                bestPartialScore = grade.getPartialScore();
            }
        return bestPartialGrade.getStudent();
    }
}

