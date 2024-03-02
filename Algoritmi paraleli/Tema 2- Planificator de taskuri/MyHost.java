/* Implement this class. */

import java.util.Iterator;
import java.util.concurrent.PriorityBlockingQueue;

public class MyHost extends Host {

    PriorityBlockingQueue<Task> queue;
    int executingTask, flag2, flag1;
    Task task_aux1, task_aux2, task = null;

    public MyHost() {
        queue = new PriorityBlockingQueue<>();
    }


    @Override
    public void run() {

        // cat timp nodul mai are task uri in coada, scoate unul
        while (!Thread.currentThread().isInterrupted()) {

            try {
                Iterator<Task> iterator = queue.iterator();
                Task currentTask = null;

                // verific daca exista un task cu prioritate mai mare
                flag1 = 0;
                while (iterator.hasNext()) {
                    task_aux1 = iterator.next();
                    if (currentTask == null ) {
                        currentTask = task_aux1;
                    }
                    if(task_aux1.getPriority() > currentTask.getPriority()) {
                        currentTask = task_aux1;
                        flag1 = 1;
                    }
                }
                // s-a gasit task cu prioritate mai mare
                if(flag1 == 1) {
                    task = currentTask;
                    boolean aux = queue.remove(currentTask);
                    if (!aux) {
                        System.out.println("Elementul nu a fost gasit in coada");
                    }
                } else {
                    // altfel iau urmatorul task din coada
                    task = queue.take();
                }

            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
                break;
            }


            // daca task-ul nu e null sii daca mai are de rulat
            if(task != null && task.getLeft() > 0) {

               synchronized (this) {
                    executingTask = 1;

                    //  ma asigur ca e momentul ca task ul sa se execute
                    if( Math.round(Timer.getTimeDouble()) < task.getStart()) {

                        try {
                            sleep((long) (1000 * (task.getStart() - Timer.getTimeDouble())));
                        } catch (InterruptedException e) {
                            throw new RuntimeException(e);
                        }
                    }

                    flag2 = 0;

                    // cat timp mai are de executat si nu a fost preemptat, execut cate o secunda din task-ul
                    while(task.getLeft() != 0 && flag2 == 0) {

                        if(task.isPreemptible()) {
                            // verific daca a aparut un task cu prioritate mai amre
                            Iterator<Task> iterator = queue.iterator();
                            while (iterator.hasNext()) {
                                task_aux2 = iterator.next();

                                // daca noul task are prio mai mare si daca e momentul sa se excuta
                                if(task_aux2.getPriority() > task.getPriority() && task_aux2.getStart() <=  Timer.getTimeDouble()) {
                                    // marchez acest lucru si pun task-ul vechi inapoi in coada
                                    flag2 = 1;
                                    queue.add(task);
                                }
                            }
                        }

                        // daca task-ul curent nu a fost preemptat, execut cate o secunda din task
                        if(flag2 == 0) {
                            try {
                                sleep(1000);
                                task.setLeft(task.getLeft() - 1);
                            } catch (InterruptedException e) {
                                throw new RuntimeException(e);
                            }
                        }
                    }

                    // apelez metoda finish, odata ce task-ul a fost incheiat 
                    if(task.getLeft() == 0) {
                        task.finish();
                    }
                    executingTask = 0;
               }
            }
        }
    }

    
    @Override
    public void addTask(Task task) {
        // adaug task-ul in coada no
        queue.add(task);
    }

    @Override
    public int getQueueSize() {
        // returnez dimensiuna cozii de task-uri, adaugand task-ul care ruleaza in acel moment
        return queue.size() + executingTask;
    }

    @Override
    public long getWorkLeft() {
        Task task_aux;
        long work_left = 0;

        // in work_left adun durata executarii task-urilor din coada
        Iterator<Task> iterator = queue.iterator();
        while(iterator.hasNext()) {
            task_aux = iterator.next();
            work_left += task_aux.getLeft();
        }

        // iau in considerare si task-ul care ruleaza in acel moment(si nu mai e in coada)
        if (executingTask == 1) {
            work_left += task.getLeft();
        }

        work_left = Math.round(work_left);
        return work_left;
    }

    @Override
    public void shutdown() {
        this.interrupt();
    }
}