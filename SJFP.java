package sjfp;

import java.util.*;

class Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;

    Process(int id, int arrivalTime, int burstTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
        this.remainingTime = burstTime;
    }
}

public class SJFP {
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
            processes.add(new Process(i, arrivalTime, burstTime));
        }

        processes.sort(Comparator.comparingInt(p -> p.arrivalTime));

        int currentTime = 0;
        int completed = 0;
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;

        while (completed < n) {
            Process currentProcess = null;
            int minRemainingTime = Integer.MAX_VALUE;

            for (Process p : processes) {
                if (p.arrivalTime <= currentTime && p.remainingTime > 0 && p.remainingTime < minRemainingTime) {
                    minRemainingTime = p.remainingTime;
                    currentProcess = p;
                }
            }

            if (currentProcess == null) {
                currentTime++;
                continue;
            }

            currentProcess.remainingTime--;
            currentTime++;

            if (currentProcess.remainingTime == 0) {
                completed++;
                currentProcess.completionTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;

                totalWaitingTime += currentProcess.waitingTime;
                totalTurnaroundTime += currentProcess.turnaroundTime;
            }
        }

        System.out.println("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\tCompletion Time");
        for (Process p : processes) {
            System.out.println(p.id + "\t\t" + p.arrivalTime + "\t\t" + p.burstTime + "\t\t" + p.waitingTime + "\t\t" + p.turnaroundTime + "\t\t" + p.completionTime);
        }

        float averageWaitingTime = (float) totalWaitingTime / n;
        float averageTurnaroundTime = (float) totalTurnaroundTime / n;

        System.out.println("\nAverage Waiting Time: " + averageWaitingTime);
        System.out.println("Average Turnaround Time: " + averageTurnaroundTime);
    }
}