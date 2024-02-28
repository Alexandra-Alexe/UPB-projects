import java.util.ArrayList;
import java.util.Scanner;

public abstract class User {
    private String firstName, lastName;
    public User(String firstName, String lastName) {
        this.firstName = firstName;
        this.lastName = lastName;
    }
    public String toString() {
        return firstName + " " + lastName;
    }
    public String getFirstName () {
        return  firstName;
    }
    public String getLastName() {
        return lastName;
    }
}
class Student extends User implements Comparable {
    private Parent mother = null, father = null;
    public Student (String firstname, String lastName) {
        super(firstname,lastName);
    }
    public Parent getMother() {
        return this.mother;
    }
    public Parent getFather() {
        return this.father;
    }
    public void setFather(Parent father) {
        this.father = father;
    }
    public void setMother(Parent mother) {
        this.mother = mother;
    }

    public String getCompleteName() {
        return this.getLastName() + " " + this.getFirstName();
    }

    @Override
    public int compareTo(Object student) {

        return this.getLastName().compareTo(((Student)student).getLastName());
    }

}
class Parent extends User implements Observer{
    public Parent (String firstname, String lastName) {
        super(firstname,lastName);
    }
    Catalog catalog;
    @Override
    public void update(Notification notification) {
        System.out.println(notification);
    }
    public void setCatalog(Catalog catalog) {
        this.catalog = catalog;
        catalog.addObserver(this);
    }
}
class Teacher extends User implements Element{

    public Teacher (String firstname, String lastName) {
        super(firstname,lastName);
    }

    @Override
    public void accept(Visitor visitor)
    {
        visitor.visit(this);
    }
}
class Assistant extends User implements Element {
    public Assistant (String firstname, String lastName) {
        super(firstname,lastName);
    }


    @Override
    public void accept(Visitor visitor) {

        visitor.visit(this);
    }
}
class UserFactory {
    User getUser(String type, String firstname, String lastname) {
        if ( type == "Student" ) {
            Student s = new Student(firstname,lastname);
            return s;
        }
        if ( type == "Parent" ) {
            Parent p = new Parent(firstname,lastname);
            return p;
        }
        if ( type == "Assistant" ) {
            Assistant a = new Assistant(firstname,lastname);
            return a;
        }
        if ( type == "Teacher" ) {
            Teacher t = new Teacher(firstname,lastname);
            return t;
        }
        return null;
    }
}



