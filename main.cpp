#include<iostream>
#include<stdio.h>
#include<conio.h>
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
            ++total_time;
        }
    }
}

int main() {
    system("color 1F");
    char welcome[100] = "\t\t\t\t\t\t\t-:Multilevel queue scheduler:-\n";
    for(int i = 0; i < strlen(welcome); i++){
        cout << welcome[i];
        Sleep(50);
    }

    char question[500] = "\nQuestion: Design a scheduler with multilevel queue having two queues which will schedule the processes on the basis of pre-emptive shortest remaining processing time first algorithm (SROT) followed by a scheduling in which each process will get 2 units of time to execute. Also note that queue 1 has higher priority than queue 2. Consider the following set of processes (for reference)with their arrival times and the CPU burst times in milliseconds.\n";
    for(int i = 0; i < strlen(question); i++){
        cout << question[i];
        Sleep(5);
    }

    char c[100] = "\nEnter total process: ";
    for(int i = 0; i < strlen(c); i++){
        cout << c[i];
        Sleep(50);
    }
    cin >> total_process;
    process = new processes[total_process];

    for (int i = 0; i < total_process; i++) {
        cout << "\nProcess P" << (i+1) << endl;
        cout << "\tP" << (i+1) << " Arrival Time: ";
        cin >> process[i].AT;
        cout << "\tP" << (i+1) << " Burst Time: ";
        cin >> process[i].BT;
        cout << "\tP" << (i+1) << " Queue: ";
        cin >> process[i].queue;
        process[i].fixed_BT = process[i].BT;
    }

    total_queue = max_queue();

    system("cls");

    for(int i = 0; i < strlen(welcome); i++){
        cout << welcome[i];
        Sleep(50);
    }
    cout << "\nGantt Chart\n";
    process_execution();

    cout << "\n\nAll process executed\n";

    getch();

    cout << "\n\nProcess\t Arrival Time\t Burst Time\t Queue\t Completion Time\t Turn Around Time\t Waiting Time\t\n\n";

    for (int i = 0; i < total_process; i++) {
        cout << "  P"<<(i+1) << "\t\t" << process[i].AT << "\t\t" << process[i].fixed_BT << "\t  " << process[i].queue <<
             "\t\t" << process[i].CT << "\t\t\t" << process[i].TAT << "\t\t\t" << process[i].WT << endl << endl;
    }

    getch();

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

    getch();

    char about[200] = "\n\t\tName: Utsab Sen\n\t\tRegistration No: 11709492\n\t\tRoll No: 22\n\t\tSection: K17TA\n\t\tLOVELY PROFESSIONAL UNIVERSITY\n\t\t...Thank you...\n";
    for(int i = 0; i < strlen(about); i++){
        cout << about[i];
        Sleep(15);
    }
}
