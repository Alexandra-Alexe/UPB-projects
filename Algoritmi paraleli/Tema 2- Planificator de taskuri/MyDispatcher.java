/* Implement this class. */

import java.util.List;

public class MyDispatcher extends Dispatcher {

    int id = 0;
    int aux;

    public MyDispatcher(SchedulingAlgorithm algorithm, List<Host> hosts) {
        super(algorithm, hosts);
    }


    @Override
    public synchronized void addTask(Task task) {

        // setez work_left a fiecarui task
        task.setLeft(task.getDuration() / 1000);

        if (algorithm == SchedulingAlgorithm.ROUND_ROBIN ) {
            // alocarea task-urilor pe masura ce vin
            aux = (id + 1) % hosts.size();
            hosts.get(aux).addTask(task);
            id = aux;
        }
        if (algorithm == SchedulingAlgorithm.SHORTEST_QUEUE) {
            
            long min = 1000000;
            int index = 0;

            for (int j = 0; j < hosts.size(); j++) {
                Host host = hosts.get(j);
                // determin cea mai scurta coada si ii retin pozitia in variabila index
                if(host.getQueueSize() < min) {
                    min = host.getQueueSize();
                    index = j;
                } else if(host.getQueueSize() == min && host.getId() < hosts.get(index).getId()) {
                    index = j;
                }
            }
            hosts.get(index).addTask(task);
        }

        if(algorithm == SchedulingAlgorithm.SIZE_INTERVAL_TASK_ASSIGNMENT) {
            // politica SITA, dictata de tipul task-ului
            if(task.getType() == TaskType.SHORT) {
                hosts.get(0).addTask(task);
            }
            if(task.getType() == TaskType.MEDIUM) {
                hosts.get(1).addTask(task);
            }
            if(task.getType() == TaskType.LONG) {
                hosts.get(2).addTask(task);
            }
        }

        if(algorithm == SchedulingAlgorithm.LEAST_WORK_LEFT) {
            long min = 1000000;
            int index = 0;

            for (int j = 0; j < hosts.size(); j++) {
                Host host = hosts.get(j);
                // determin nodul cu cel mai mic volum de munca si ii retin pozitia in variabila index
                if(host.getWorkLeft() < min) {
                    min = host.getWorkLeft();
                    index = j;
                } else if(host.getWorkLeft() == min && host.getId() < hosts.get(index).getId()) {
                    index = j;
                }
            }
             hosts.get(index).addTask(task);
        }
    }
}
