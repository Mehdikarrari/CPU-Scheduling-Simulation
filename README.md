'''input structure:
'''first line: number of process
'''second line: quantom time
'''other lines: in each lines 6 integers
first integer: pid
second integer: arrival time
third integer: burst time 
4'th to 6'th integer: 0
first input:
3
4
1 0 10 0 0 0
2 1 5 0 0 0
3 2 8 0 0 0

first output:
FCFS: Turnaround = 15 ,Waiting = 7.33333 ,Response = 7.33333
SJF: Turnaround = 15 ,Waiting = 7.33333 ,Response = 7.33333
RR: Turnaround = 19.3333 ,Waiting = 11.6667 ,Response = 3


second input:
4
2
1 0 4 0 0 0
2 1 3 0 0 0
3 2 1 0 0 0
4 3 2 0 0 0

second output:
FCFS: Turnaround = 5.75 ,Waiting = 3.25 ,Response = 3.25
SJF: Turnaround = 5 ,Waiting = 2.5 ,Response = 2.5
RR: Turnaround = 6.25 ,Waiting = 3.75 ,Response = 1.25
