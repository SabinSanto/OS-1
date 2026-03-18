#include <stdio.h>
#include <string.h>

struct Process {
    char pid[10];
    int at, bt;
    int wt, tat;
    int completed;
};

int main() {
    int n, i, j, time = 0, completed = 0;
    float total_wt = 0, total_tat = 0;

    printf("Enter number of processes:\n");
    scanf("%d", &n);

    struct Process p[n];

    // Input
    for(i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].pid, &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    while(completed < n) {
        int idx = -1;
        int min_bt = 1e9;

        // Find process with minimum burst time among arrived processes
        for(i = 0; i < n; i++) {
            if(p[i].at <= time && p[i].completed == 0) {
                if(p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
            }
        }

        if(idx != -1) {
            // Execute process
            time += p[idx].bt;
            p[idx].tat = time - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_wt += p[idx].wt;
            total_tat += p[idx].tat;

            p[idx].completed = 1;
            completed++;
        } else {
            time++; // CPU idle
        }
    }

    // Output
    printf("Waiting Time:\n");
    for(i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].wt);
    }

    printf("Turnaround Time:\n");
    for(i = 0; i < n; i++) {
        printf("%s %d\n", p[i].pid, p[i].tat);
    }

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
