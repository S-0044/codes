package FCFS;

import java.util.*;

class process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;

    process(int id, int arrivalTime, int burstTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }
}

public class FCFS
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        List<process> processes = new ArrayList<>();

        for (int i = 1; i <= n; i++)
        {
            System.out.print("Enter arrival time for process " + i + ": ");
            int arrivalTime = sc.nextInt();

            System.out.print("Enter burst time for process " + i + ": ");
            int burstTime = sc.nextInt();

            processes.add(new process(i, arrivalTime, burstTime));
        }

        processes.sort(Comparator.comparingInt(p -> p.arrivalTime));

        int currentTime = 0;
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        int completedProcesses = 0;
        int lastCompletionTime = 0;

        System.out.println("\nPid\tAT\tBT\tWT\tTAT\tCT");

        for (process p : processes)
        {
            if (currentTime < p.arrivalTime)
            {
                currentTime = p.arrivalTime;
            }

            p.waitingTime = currentTime - p.arrivalTime;
            p.turnaroundTime = p.waitingTime + p.burstTime;
            currentTime += p.burstTime;
            p.completionTime = currentTime;

            totalWaitingTime += p.waitingTime;
            totalTurnaroundTime += p.turnaroundTime;
            completedProcesses++;
            lastCompletionTime = p.completionTime;

            System.out.println(p.id + "\t" + p.arrivalTime + "\t" + p.burstTime + "\t" + p.waitingTime + "\t" + p.turnaroundTime + "\t" + p.completionTime);
        }

        float averageWaitingTime = (float) totalWaitingTime / n;
        float averageTurnaroundTime = (float) totalTurnaroundTime / n;
        float throughput = (float) completedProcesses / lastCompletionTime;

        System.out.println("\nAverage Waiting Time: " + averageWaitingTime);
        System.out.println("Average Turnaround Time: " + averageTurnaroundTime);
    }
}