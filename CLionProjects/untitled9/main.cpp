#include <iostream>
using namespace std;
typedef struct {
    int pid;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int startTime;
    int completionTime;
} Process;

typedef struct {
    float avgTurnaround;
    float avgWaiting;
    float avgResponse;
} Metrics;


Metrics fcfs_metrics(Process proc[], int n){
    Metrics output;
    int t = proc[0].arrivalTime;
    output.avgResponse = 0;
    output.avgTurnaround = 0;
    output.avgWaiting = 0;
    for(int i = 0;i < n;i++) {
        output.avgResponse += t - proc[i].arrivalTime;
        output.avgTurnaround += t + proc[i].burstTime - proc[i].arrivalTime;
        output.avgWaiting += t - proc[i].arrivalTime;
        t += proc[i].burstTime;
    }
    output.avgResponse /= n;
    output.avgTurnaround /= n;
    output.avgWaiting /= n;
    return output;
}


Metrics sjf_metrics(Process proc[], int n){
    Metrics output;
    int t = proc[0].arrivalTime;
    output.avgResponse = 0;
    output.avgTurnaround = 0;
    output.avgWaiting = 0;
    int k = 0;
    int p = proc[0].burstTime;
    int pid = proc[0].pid;
    while (k < n) {
        int i = 0;
        while (proc[i].arrivalTime <= t)
        {
            if((proc[i].burstTime < p || proc[pid - 1].completionTime != 0) && proc[i].completionTime == 0) {
                pid = proc[i].pid;
                p = proc[i].burstTime;
            }
            i++;
        }
        output.avgResponse += t - proc[pid - 1].arrivalTime;
        output.avgTurnaround += t + proc[pid - 1].burstTime - proc[pid - 1].arrivalTime;
        output.avgWaiting += t - proc[pid - 1].arrivalTime;
        t += proc[pid - 1].burstTime;
        proc[pid - 1].completionTime = t;
        k++;

    }
    output.avgResponse /= n;
    output.avgTurnaround /= n;
    output.avgWaiting /= n;
    return output;
}


Metrics rr_metrics(Process proc[], int n, int timeQuantum){Metrics output;
    int t = proc[0].arrivalTime;
    output.avgResponse = 0;
    output.avgTurnaround = 0;
    output.avgWaiting = 0;
    int k = 0;
    while (k < n) {
        int i = 0;
        while (proc[i].arrivalTime <= t && k < n && i < n)
        {
            if(proc[i].startTime == 0) {
                proc[i].startTime = 1;
                output.avgResponse += t - proc[i].arrivalTime;
            }
            if(proc[i].completionTime == 0 && proc[i].remainingTime > timeQuantum) {
                proc[i].remainingTime -= timeQuantum;
                t += timeQuantum;
            }
            else if(proc[i].completionTime == 0 && proc[i].remainingTime <= timeQuantum) {
                t += proc[i].remainingTime;
                output.avgWaiting += t - proc[i].arrivalTime - proc[i].burstTime;
                output.avgTurnaround += t - proc[i].arrivalTime;
                k++;
            }
            i++;
        }

    }
    output.avgResponse /= n;
    output.avgTurnaround /= n;
    output.avgWaiting /= n;
    return output;
}



int main() {
    int n;
    cin >> n;
    Process process_arr[n];
    int timeQuantum;
    cin >> timeQuantum;
    for (int i = 0; i < n;i++) {
            cin >> process_arr[i].pid;
            cin >> process_arr[i].arrivalTime;
            cin >> process_arr[i].burstTime;
            cin >> process_arr[i].completionTime;
            cin >> process_arr[i].remainingTime;
            cin >> process_arr[i].startTime;
            process_arr[i].remainingTime = process_arr[i].burstTime;
    }
    Metrics rr_out = rr_metrics(process_arr,n,timeQuantum);
    Metrics sjf_out = sjf_metrics(process_arr,n);
    Metrics fcfs_out = fcfs_metrics(process_arr,n);
    cout << "FCFS: ";
    cout << "Turnaround = " << fcfs_out.avgTurnaround << " ,";
    cout << "Waiting = " << fcfs_out.avgWaiting << " ,";
    cout << "Response = " << fcfs_out.avgResponse << endl;
    cout << "SJF: ";
    cout << "Turnaround = " << sjf_out.avgTurnaround << " ,";
    cout << "Waiting = " << sjf_out.avgWaiting << " ,";
    cout << "Response = " << sjf_out.avgResponse << endl;
    cout << "RR: ";
    cout << "Turnaround = " << rr_out.avgTurnaround << " ,";
    cout << "Waiting = " << rr_out.avgWaiting << " ,";
    cout << "Response = " << rr_out.avgResponse << endl;
}