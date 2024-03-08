// OS HW3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <queue>
#include <random>
using namespace std;

class Process
{
public:
    int process_id;     // Process ID
    int arrival_time;   // Arrival Time of the process
    int lottery_tickets; // Represents burst time
private:

};


class Scheduler : public Process
{
public:
    double roundRobin(const vector<Process>& processes, int quantum) {
        queue<Process> process_queue;   // Queue to store processes
        int current_time = 0;           // Current time initialized to 0
        int total_waiting_time = 0;     // Total waiting time initialized to 0
        int flag = 0;                   // Used to trigger when first proccess is done

        vector<Process> remaining_processes = processes;   // Copy of processes vector

        while (!process_queue.empty() || !remaining_processes.empty()) { // Continue until all processes are executed
            if (!remaining_processes.empty()) {
                // Add processes to the queue that have arrived by the current time
                while (!remaining_processes.empty() && remaining_processes.front().arrival_time <= current_time) {
                    process_queue.push(remaining_processes.front());
                    remaining_processes.erase(remaining_processes.begin());
                }
            }

            if (!process_queue.empty()) {
                Process current_process = process_queue.front(); // Get the next process from the queue
                process_queue.pop();

                int execution_time = min(quantum, current_process.lottery_tickets); // Determine execution time for this quantum
                current_time += execution_time; // Increment current time
                current_process.lottery_tickets -= execution_time; // Decrease burst time of the process

                // Add arrived processes to the queue during the current time interval
                while (!remaining_processes.empty() && remaining_processes.front().arrival_time <= current_time) {
                    process_queue.push(remaining_processes.front());
                    remaining_processes.erase(remaining_processes.begin());
                }

                if (current_process.lottery_tickets > 0) { // If burst time is still remaining
                    process_queue.push(current_process); // Add the process back to the queue
                }
                else { // Process has finished executing
                    if (flag == 0) {
                        cout << "Process " << current_process.process_id << " wins the lottery" << endl; // Print out Winner
                        flag++; // Triggers so no other results appear 
                    }
                }
            }
            else { // No process in the queue, move time to the next process arrival time
                current_time = remaining_processes.front().arrival_time;
            }
        }
        return 0;
    }

private:

};




int main() {
    Process proc;
    Scheduler sch;

    random_device rd;      // sets up device to randomize
    uniform_int_distribution<int> dist(1, 100); // sets the range of random numbers between 1 and 100

    // Define a vector of processes with their process ID, arrival time, and random lottery ticket
    vector<Process> processes = {
        {1, 0, dist(rd)},  // Process 1 arrives at time 0 and random lottery ticket number
        {2, 1, dist(rd)},  // Process 2 arrives at time 1 and random lottery ticket number
        {3, 2, dist(rd)},  // Process 3 arrives at time 2 and random lottery ticket number
        {4, 4, dist(rd)}   // Process 4 arrives at time 3 and random lottery ticket number
    };
    int quantum = 2; // Time quantum

    // Runs the scheduler
    sch.roundRobin(processes, quantum);
    return 0;
}