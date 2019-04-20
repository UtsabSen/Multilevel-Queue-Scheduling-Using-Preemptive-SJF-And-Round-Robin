#include<stdio.h>
#include<iostream>
using namespace std;

int total_process, total_time = 0, total_queue, TQ = 2;

struct processes{
    int AT, BT, queue, CT = 0, TAT = 0, WT = 0, fixed_BT;
}*process;

int max_queue(){
    int max = 0;
    for (int i = 0; i < total_process; i++) {
        if (process[i].queue > max){
            max = process[i].queue;
        }
    }
    return max;
}



int main(){
    cout << "Enter total process: ";
    cin >> total_process;
    process = new processes[total_process];

    for (int i = 0; i < total_process; i++){
        cout << "\nProcess P" << (i+1) << endl;
        cout << "AT: ";
        cin >> process[i].AT;
        cout << "BT: ";
        cin >> process[i].BT;
        cout << "Queue: ";
        cin >> process[i].queue;
        process[i].fixed_BT = process[i].BT;
    }

    cout << "\n\nProcess\t Arrival Time\t Burst Time\t Queue\t Completion Time\t Turn Around Time\t Waiting Time\t\n";
    for (int i = 0; i < total_process; i++) {
        cout << "  P"<<(i+1) << "\t\t" << process[i].AT << "\t\t" << process[i].fixed_BT << "\t  " << process[i].queue <<
             "\t\t" << process[i].CT << "\t\t\t" << process[i].TAT << "\t\t\t" << process[i].WT << endl;
    }

    total_queue = max_queue();
}
