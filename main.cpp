#include<stdio.h>
#include<iostream>
#include<windows.h>
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

int high_priority_queue(){
    for (int i = 0; i < total_queue; i++) {
        for (int j = 0; j < total_process; j++) {
            if((process[j].queue == i && process[j].BT > 0) && (total_time >= process[j].AT)){
                return process[j].queue;
            }
        }
    }
}

int least_BT(int queue){
    int small_BT = 0, flag = 0;
    for (int i = 0; i < total_process; i++) {
        if (process[i].BT > 0 && process[i].queue == queue && total_time >= process[i].AT){
            small_BT = process[i].BT;
            flag = i;
            break;
        }
    }

    for (int i = 0; i < total_process; i++) {
        if (small_BT > process[i].BT && process[i].BT > 0 && process[i].queue == queue && total_time >= process[i].AT){
            small_BT = process[i].BT;
            flag = i;
        }
    }
    return flag;
}

int complete_process(){
    for (int i = 0; i < total_process; i++){
        if (process[i].BT > 0){
            return 0;
        }
    }
    return 1;
}

int arrive_process(){
    for (int i = 0; i < total_process; i++) {
        if(process[i].BT > 0 && total_time >= process[i].AT){
            return 0;
        }
    }
    return 1;
}

void process_execution(){

    int t[50] = {0};
    int c;

    int checkpoint = 1;
    while (!complete_process()){
        if (!arrive_process()){
            int p_id = least_BT(high_priority_queue());
            for (int i = 0; i < TQ; i++) {
                process[p_id].BT--;
                total_time++;
                if(checkpoint == 1){
                    c = process[p_id].AT;
                    checkpoint = 0;
                    cout << "Start: " << c << "\t";
                }
                c++;
                cout << "P" << (p_id+1) <<" -> "<< c << " \t";
                t[i] = c;
                Sleep(200);

                for (int j = 0; j < total_process; j++) {
                    if(j != p_id && total_time > process[j].AT && process[j].BT > 0){
                        process[j].WT++;
                    }
                }

                if (process[p_id].BT == 0){
                    process[p_id].CT = total_time;
                    process[p_id].TAT = process[p_id].CT - process[p_id].AT;
                    break;
                }

                if (high_priority_queue() < process[p_id].queue){
                    break;
                }
            }
        } else{
            total_time++;
        }
    }
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


    total_queue = max_queue();

    cout << "Gantt Chart\n";
    process_execution();

    cout << "\n\nAll process executed\n";

    cout << "\n\nProcess\t Arrival Time\t Burst Time\t Queue\t Completion Time\t Turn Around Time\t Waiting Time\t\n";
    for (int i = 0; i < total_process; i++) {
        cout << "  P"<<(i+1) << "\t\t" << process[i].AT << "\t\t" << process[i].fixed_BT << "\t  " << process[i].queue <<
             "\t\t" << process[i].CT << "\t\t\t" << process[i].TAT << "\t\t\t" << process[i].WT << endl;
    }

    float total_TAT = 0, total_WT = 0;
    float avg_TAT = 0, avg_WT = 0;
    for (int i = 0; i < total_process; i++) {
        total_TAT += process[i].TAT;
    }
    avg_TAT = total_TAT / total_process;
    for (int i = 0; i < total_process; i++) {
        total_WT += process[i].WT;
    }
    avg_WT = total_WT / total_process;

    cout << "\nAverage Turn Around Time: " << avg_TAT << endl;
    cout << "\nAverage Waiting Time: " << avg_WT << endl << endl;

}
