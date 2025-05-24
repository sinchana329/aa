#include <stdio.h>

struct Process {
    int id;          
    int burst_time; 
    int remaining_time;
    int waiting_time; 
    int turnaround_time; 
};


void round_robin(struct Process processes[], int n, int quantum) {
    int time = 0;
    int completed = 0;
    
    while (completed < n) {
        for (int i = 0; i < n; i++) {
           
            if (processes[i].remaining_time > 0) {
              
                int time_slice = (processes[i].remaining_time > quantum) ? quantum : processes[i].remaining_time;
                time += time_slice;
                processes[i].remaining_time -= time_slice;

            
                if (processes[i].remaining_time == 0) {
                    processes[i].turnaround_time = time;
                    processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
                    completed++;
                }
            }
        }
    }
}


void calculate_metrics(struct Process processes[], int n) {
    int total_waiting_time = 0, total_turnaround_time = 0;

    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for Process P%d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time; 
        processes[i].waiting_time = 0;
        processes[i].turnaround_time = 0;
    }

    int quantum;
    printf("Enter the time quantum: ");
    scanf("%d", &quantum);

    printf("\nRunning Round Robin Scheduling with quantum size %d:\n", quantum);
    
    round_robin(processes, n, quantum);

 
    calculate_metrics(processes, n);

    return 0;
}
