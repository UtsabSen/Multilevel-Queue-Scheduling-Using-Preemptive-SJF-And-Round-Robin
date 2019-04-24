#include<iostream>      // Include required header files
#include<stdio.h>
#include<conio.h>
#include<windows.h>
using namespace std;

int total_process, total_time = 0, total_queue, TQ = 2;     // Define global variables of type integer

struct processes{       // Define structure
    int AT, BT, queue, CT = 0, TAT = 0, WT = 0, fixed_BT;
}*process;      //Define structure variable

int max_queue(){        // Define max_queue function of type integer
    int max = 0;
    for (int i = 0; i < total_process; i++) {
        if (process[i].queue > max){
            max = process[i].queue;     // Return queue processes
        }
    }
    return max;     // Return maximum queue value
}

int high_priority_queue(){      // Define high_priority_queue function of type integer
    for (int i = 0; i < total_queue; i++) {
        for (int j = 0; j < total_process; j++) {
            if((process[j].queue == i && process[j].BT > 0) && (total_time >= process[j].AT)){
                return process[j].queue;        // Return processes from the queue which has higher priority
            }
        }
    }
}

int least_BT(int queue){        // Define least_BT function of type integer
    int small_BT = 0, flag = 0;
    for (int i = 0; i < total_process; i++) {
        if (process[i].BT > 0 && process[i].queue == queue && total_time >= process[i].AT){     // Check for the minimum burst time of processes
            small_BT = process[i].BT;
            flag = i;
            break;
        }
    }

    for (int i = 0; i < total_process; i++) {
        if (small_BT > process[i].BT && process[i].BT > 0 && process[i].queue == queue && total_time >= process[i].AT){     // Check burst time, arrival time of processes
            small_BT = process[i].BT;
            flag = i;
        }
    }
    return flag;        // Return process id using flag variable with smallest burst time
}

int complete_process(){     // Define complete_process function of type integer
    for (int i = 0; i < total_process; i++){
        if (process[i].BT > 0){     // Check if burst time of a process is left or not
            return 0;       // Return false
        }
    }
    return 1;       // Return True
}

int arrive_process(){       // Define arrive_process function of type integer
    for (int i = 0; i < total_process; i++) {
        if(process[i].BT > 0 && total_time >= process[i].AT){       // Check which process should arrive next
            return 0;       // Return false
        }
    }
    return 1;       // Return true
}

void process_execution(){       // Define process_execution function of type void

    int t[50] = {0};        // Integer array of size 50 with default value zero
    int c;

    int checkpoint = 1;
    while (!complete_process()){        // Check if any process is complete or not by checking its burst time       // Call complete_process function
        if (!arrive_process()){     // Check  which process should arrive next      // Call arrive_process function
            int p_id = least_BT(high_priority_queue());     // Store process id of smallest burst time in p_id variable
            for (int i = 0; i < TQ; i++) {
                process[p_id].BT--;     // Decrement burst time
                total_time++;       // Count the time of process execution
                if(checkpoint == 1){        // Check when process should start
                    c = process[p_id].AT;
                    checkpoint = 0;
                    cout << "Start: " << c << "\t";
                }
                c++;
                cout << "P" << (p_id+1) <<" -> "<< c << " \t";      // Print process id with process execution time in a form of gantt chart in the console
                t[i] = c;
                Sleep(200);     // Slow down print gantt chart by 20 mili second

                for (int j = 0; j < total_process; j++) {
                    if(j != p_id && total_time > process[j].AT && process[j].BT > 0){       // Check arrival time and burst time of a process
                        process[j].WT++;        // Increment waiting time
                    }
                }

                if (process[p_id].BT == 0){     // Check burst time is zero or not
                    process[p_id].CT = total_time;      // Calculate completion time
                    process[p_id].TAT = process[p_id].CT - process[p_id].AT;        // Calculate Turn Around Time
                    break;
                }

                if (high_priority_queue() < process[p_id].queue){       // Check priority
                    break;
                }
            }
        } else{
            total_time++;       // Increment time of process execution
        }
    }
}

int main() {
    system("color 1F");     // Change console color with blue background and bright white font color
    char welcome[100] = "\t\t\t\t\t\t\t-:Multilevel queue scheduler:-\n";   // Heading of the program
    for(int i = 0; i < strlen(welcome); i++){       // Print the heading with gap of 5 mili second
        cout << welcome[i];
        Sleep(50);
    }

    char question[500] = "\nQuestion: Design a scheduler with multilevel queue having two queues which \
will schedule the processes on the basis of pre-emptive shortest remaining processing time first \
algorithm (SROT) followed by a scheduling in which each process will get 2 units of time to execute.\
Also note that queue 1 has higher priority than queue 2. Consider the following set of processes \
(for reference)with their arrival times and the CPU burst times in milliseconds.\n";       // Store the question in question character array of size 500
    for(int i = 0; i < strlen(question); i++){      // Print the question with gap of 0.5 mili second
        cout << question[i];
        Sleep(5);
    }

    char c[100] = "\nEnter total process: ";
    for(int i = 0; i < strlen(c); i++){
        cout << c[i];
        Sleep(50);
    }
    cin >> total_process;       // Take total process as an input from the user
    process = new processes[total_process];

    for (int i = 0; i < total_process; i++) {
        cout << "\nProcess P" << (i+1) << endl;     // Print process id
        cout << "\tP" << (i+1) << " Arrival Time: ";
        cin >> process[i].AT;       // Take arrival time as an input from the user
        cout << "\tP" << (i+1) << " Burst Time: ";
        cin >> process[i].BT;       // Take burst time as an input from the user
        cout << "\tP" << (i+1) << " Queue: ";
        cin >> process[i].queue;        // Take queue number as an input from the user
        process[i].fixed_BT = process[i].BT;        // Backup burst time
    }

    total_queue = max_queue();      // Call max_queue function and store the maximum queue in total_queue variable

    system("cls");      // Clear the console screen

    for(int i = 0; i < strlen(welcome); i++){       // Print the heading with gap of 5 mili second
        cout << welcome[i];
        Sleep(50);
    }
    cout << "\nGantt Chart\n";
    process_execution();        // Call process_execution function and print the gantt chart

    cout << "\n\nAll process executed\n";

    cout << "\n\nProcess\t Arrival Time\t Burst Time\t Queue\t Completion Time\t Turn Around Time\t Waiting Time\t\n\n";        // Print table header

    for (int i = 0; i < total_process; i++) {       // Print all processes process id, arrival time, burst time, queue, completion time, turn around time, waiting time
        cout << "  P"<<(i+1) << "\t\t" << process[i].AT << "\t\t" << process[i].fixed_BT << "\t  " << process[i].queue <<
             "\t\t" << process[i].CT << "\t\t\t" << process[i].TAT << "\t\t\t" << process[i].WT << endl << endl;
    }

    float total_TAT = 0, total_WT = 0;
    float avg_TAT = 0, avg_WT = 0;
    for (int i = 0; i < total_process; i++) {       // Calculate total turn around time
        total_TAT += process[i].TAT;
    }
    avg_TAT = total_TAT / total_process;        // Calculate average turn around time

    for (int i = 0; i < total_process; i++) {       // Calculate total waiting time
        total_WT += process[i].WT;
    }
    avg_WT = total_WT / total_process;      // Calculate average waiting time

    cout << "\nAverage Turn Around Time: " << avg_TAT << endl;      // Print average turn around time
    cout << "\nAverage Waiting Time: " << avg_WT << endl << endl;       // Print average waiting time

    cout << "\nPress any key to continue...\n\n";       // Take user input for further details

    getch();        // Take user input but do not store it

    char about[200] = "\n\t\tName: Utsab Sen\n\t\tRegistration No: 11709492\n\t\tRoll No: 22\n\t\tSection: K17TA\n\t\tLOVELY PROFESSIONAL UNIVERSITY\n\t\t...Thank you...\n";       // Student(My) details
    for(int i = 0; i < strlen(about); i++){     // Print student details with gap of 1.5 mili second
        cout << about[i];
        Sleep(15);
    }
}
