package priority_prem;

import java.util.*;

class Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;
    int priority;

    Process(int id, int arrivalTime, int burstTime, int priority) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.remainingTime = burstTime;
        this.priority = priority;
    }
}

public class pri_prem{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        List<Process> processes = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            System.out.print("Enter arrival time for process " + i + ": ");
            int arrivalTime = sc.nextInt();
            System.out.print("Enter burst time for process " + i + ": ");
            int burstTime = sc.nextInt();
            System.out.print("Enter priority for process " + i + ": ");
            int priority = sc.nextInt();
            processes.add(new Process(i, arrivalTime, burstTime, priority));
        }

        int currentTime = 0;
        int completed = 0;
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;

        PriorityQueue<Process> priorityQueue = new PriorityQueue<>(Comparator.comparingInt(p -> p.priority));

        System.out.println("\nP\tAT\tBT\tPri\tWT\tTT\tCT");

        while (completed < n) {
            for (Process p : processes) {
                if (p.arrivalTime <= currentTime && p.remainingTime > 0 && !priorityQueue.contains(p)) {
                    priorityQueue.add(p);
                }
            }

            if (priorityQueue.isEmpty()) {
                currentTime++;
                continue;
            }

            Process currentProcess = priorityQueue.poll();

            currentTime += currentProcess.burstTime;
            currentProcess.remainingTime = 0;
            completed++;
            currentProcess.completionTime = currentTime;
            currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
            currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
            totalWaitingTime += currentProcess.waitingTime;
            totalTurnaroundTime += currentProcess.turnaroundTime;

            System.out.println(currentProcess.id + "\t" + currentProcess.arrivalTime + "\t" + currentProcess.burstTime + "\t" + currentProcess.priority + "\t" + currentProcess.waitingTime + "\t" + currentProcess.turnaroundTime + "\t\t" + currentProcess.completionTime);
        }

        float averageWaitingTime = (float) totalWaitingTime / n;
        float averageTurnaroundTime = (float) totalTurnaroundTime / n;

        System.out.println("\nAverage Waiting Time: " + averageWaitingTime);
        System.out.println("Average Turnaround Time: " + averageTurnaroundTime);
    }
}