import java.util.ArrayList;
import java.util.List;
import java.util.Vector;

public class Catalog implements Subject {
    String  name;

    private static Catalog catalog;
    public List<Course> listCourses;
    Vector<Observer> observers;
    Notification notification;

    private Catalog () {
        name = "catalog1";
        listCourses = new ArrayList<>();
        observers = new Vector<>();
    }

    static public Catalog getInstance () {
        if( catalog == null)
            catalog = new Catalog();
        return catalog;
    }
    public void addCourse(Course course) {
        listCourses.add(course);
        //Nu am de ce sa apelez notigyObservers(grade) pt ca tocmai am creat
        // cursul si nu pot avea inca observers
    }
    public void removeCourse(Course course) {
        listCourses.remove(course);
    }
    public void showCourses() {
        System.out.println(listCourses);
    }


    @Override
    public void addObserver(Observer observer) {
        observers.add(observer);
    }

    @Override
    public void removeObserver(Observer observer) {
        observers.remove(observer);
    }

    @Override
    public void notifyObservers(Grade grade) {
        for (Observer observer : observers) {
            if(grade.getStudent().getMother().equals(observer)) {
                notification = new Notification(grade);
                observer.update(notification);
            }
            if(grade.getStudent().getFather().equals(observer)) {
                notification = new Notification(grade);
                observer.update(notification);
            }
        }
    }
}

