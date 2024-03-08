# Proccess Class
process_id is of type int and is the id for the process.
arrival_time is type int and is the order the process arrive in the scheduler.
lottery_tickets is type int and is the lottery number give to the process and is functionally the burst time

# Scheduler 
I used the Round Robin code found on blackboard as my base for the code and took out the part about average wait time. 
I added the flag varible as type int, and its purpose is to work as a check in the if statement where the scheduler finishes executing. 
I then print the first value to finish and increment the flag so it is not triggered again. 

# int main()
In main I initilize my two classes first.
Then using #include <random>, I set up the random number generater for the ticket numbers, and have the range be from 1 to 100.
Next I define my processes as a vector and put in the values as {process_id, arrival_time, lottery_tickets}.
Then I run the round robin scheduler. 
