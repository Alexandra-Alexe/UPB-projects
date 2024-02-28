public class BestTotalScoare implements Strategy{

    @Override
    public Student BestGrade(Course course) {
        Double bestTotalScore = 0.0;
        Grade bestTotalGrade = null;
        for ( Grade grade : course.getListGrades())
            if(grade.getTotal() > bestTotalScore) {
                bestTotalScore = grade.getTotal();
                bestTotalGrade = grade;
            }
        return bestTotalGrade.getStudent();
    }
}