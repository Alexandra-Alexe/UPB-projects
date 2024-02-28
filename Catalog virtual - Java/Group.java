import java.util.Comparator;
import java.util.TreeSet;

public class Group extends TreeSet<Student> {
    public TreeSet<Student> studentsGroup; //colectie ORDONATA de studenti ai unei grupe
    Assistant assistant;
    String ID;

    public void addStudent(Student student) {
        studentsGroup.add(student);
    }
    public Group(String ID, Assistant assistant) {
        studentsGroup = new TreeSet<>();
        this.assistant = assistant;
        this.ID = ID;
    }
    public Group(String ID, Assistant assistant, Comparator<Student> comp) {
        studentsGroup = new TreeSet();
        this.assistant = assistant;
        this.ID = ID;
    }
     public String toString() {
        return "ID grupa: " + ID + " si asistent: " + assistant;
     }
}
