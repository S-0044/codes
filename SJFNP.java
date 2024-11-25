package sjfnp;

import java.util.*;

class Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int completionTime;

    Process(int id, int arrivalTime, int burstTime) {
        this.id = id;
        this.arrivalTime = arrivalTime;
        this.burstTime = burstTime;
    }
}

public class SJFNP
{
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();

        List<Process> processes = new ArrayList<>();

        for (int i = 1; i <= n; i++)
        {
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

        System.out.println("\nPid\tAT\tBT\tWT\tTT\tCT");

        while (completed < n)
        {
            Process currentProcess = null;
            for (Process p : processes)
            {
                if (p.arrivalTime <= currentTime && p.completionTime == 0)
                {
                    if (currentProcess == null || p.burstTime < currentProcess.burstTime)
                    {
                        currentProcess = p;
                    }
                }
            }

            if (currentProcess != null)
            {
                currentProcess.waitingTime = currentTime - currentProcess.arrivalTime;
                currentProcess.turnaroundTime = currentProcess.waitingTime + currentProcess.burstTime;
                currentProcess.completionTime = currentTime + currentProcess.burstTime;
                currentTime += currentProcess.burstTime;

                totalWaitingTime += currentProcess.waitingTime;
                totalTurnaroundTime += currentProcess.turnaroundTime;
                completed++;

                System.out.println(currentProcess.id + "\t\t" + currentProcess.arrivalTime + "\t\t" + currentProcess.burstTime + "\t\t" + currentProcess.waitingTime + "\t\t" + currentProcess.turnaroundTime + "\t\t" + currentProcess.completionTime);
            }
            else
            {
                currentTime++;
            }
        }

        float averageWaitingTime = (float) totalWaitingTime / n;
        float averageTurnaroundTime = (float) totalTurnaroundTime / n;

        System.out.println("\nAverage Waiting Time: " + averageWaitingTime);
        System.out.println("Average Turnaround Time: " + averageTurnaroundTime);
    }
}