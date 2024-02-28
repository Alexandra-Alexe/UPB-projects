public class Notification {
    Grade grade;

    Notification ( Grade grade) {
        this.grade = grade;
    }

    @Override
    public String toString() {
        String notificationText = "";
        if(grade.getPartialScore() != null)
            notificationText.concat("Nota pe parcurs a studentului " + grade.getStudent().getCompleteName()
                    + " este " + grade.getPartialScore());
        if(grade.getExamScore() != null)
            notificationText.concat("Nota in examen a studentului " + grade.getStudent().getCompleteName()
                    + " este " + grade.getExamScore());
        notificationText.concat(" ");
        return notificationText;
    }
    
}

