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

public class roundRobin {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter number of processes: ");
        int n = sc.nextInt();
        System.out.print("Enter time quantum: ");
        int timeQuantum = sc.nextInt();

        List<Process> processes = new ArrayList<>();
        for (int i = 1; i <= n; i++) {
            System.out.print("Enter arrival time for process " + i + ": ");
            int arrivalTime = sc.nextInt();
            System.out.print("Enter burst time for process " + i + ": ");
            int burstTime = sc.nextInt();
            processes.add(new Process(i, arrivalTime, burstTime));
        }

        int currentTime = 0;
        int completed = 0;
        int totalWaitingTime = 0;
        int totalTurnaroundTime = 0;
        Queue<Process> queue = new LinkedList<>();

        processes.sort(Comparator.comparingInt(p -> p.arrivalTime));
        queue.addAll(processes);

        System.out.println("\nPx\tAT\tBT\tWT\tTT\tCT");

        while (completed < n) {
            Process currentProcess = queue.poll();
            if (currentProcess == null) {
                currentTime++;
                continue;
            }

            if (currentProcess.remainingTime > timeQuantum) {
                currentProcess.remainingTime -= timeQuantum;
                currentTime += timeQuantum;
            } else {
                currentTime += currentProcess.remainingTime;
                currentProcess.remainingTime = 0;
                completed++;
                currentProcess.completionTime = currentTime;
                currentProcess.turnaroundTime = currentProcess.completionTime - currentProcess.arrivalTime;
                currentProcess.waitingTime = currentProcess.turnaroundTime - currentProcess.burstTime;
                totalWaitingTime += currentProcess.waitingTime;
                totalTurnaroundTime += currentProcess.turnaroundTime;

                System.out.println(currentProcess.id + "\t" + currentProcess.arrivalTime + "\t" + currentProcess.burstTime + "\t" + currentProcess.waitingTime + "\t" + currentProcess.turnaroundTime + "\t" + currentProcess.completionTime);
            }

            for (Process p : processes) {
                if (p.arrivalTime <= currentTime && p.remainingTime > 0 && !queue.contains(p)) {
                    queue.add(p);
                }
            }

            if (currentProcess.remainingTime > 0) {
                queue.add(currentProcess);
            }

            if (queue.isEmpty() && completed < n) {
                currentTime++;
            }
        }

        float averageWaitingTime = (float) totalWaitingTime / n;
        float averageTurnaroundTime = (float) totalTurnaroundTime / n;

        System.out.println("\nAverage Waiting Time: " + averageWaitingTime);
        System.out.println("Average Turnaround Time: " + averageTurnaroundTime);
    }
}