# Mini-Projet-2

My 2nd Project for AVR Diploma under supervision of Eng Mohamed Tarek

## Alarm Feature

Using the preprocessor directives such as #define, #if and #endif to control the whole 
feature, as we can turn it on by setting SETALARM = 1 and off by setting SETALARM = 0

<a href="https://imgbb.com/"><img src="https://i.ibb.co/mqs4kyh/1.png" alt="1" border="0"></a>

#### Declaring Variables: 
1- Structure Alarm to save the time that we want the alarm to start on, and pointer to 
it so we can edit it.

2- Flag that indicates if the alarm is on or not

3- Count that is used to control for how many seconds we want our alarm to be on.

4- Function that takes the time as parameter so we can set the alarm


<a href="https://ibb.co/sW8Sxv2"><img src="https://i.ibb.co/7kscMJX/2.png" alt="2" border="0"></a>

In the ISR of the timer “each second “we will compare our time with the alarm time, if 
they are equal the buzzer, we will turn on the buzzer and make the flag = 1.

When the flag is 1, we will count from 0 to x seconds so we can turn off the buzzer after 
dedicated time “5 seconds in this code “, and we will reset the count so the alarm can go
off in the next day.


<a href="https://ibb.co/93zTdbc"><img src="https://i.ibb.co/tPks1qQ/3.png" alt="3" border="0"></a>

#### Cons:
1- We are increasing the code size inside the ISR function and that will add more time 
to serve the timer interrupt and it may affect the other interrupts by increasing their
interrupt latency time.

2- We have to set the alarm time in the code as we can’t take it as input from the user, 
but I’ll try it after the keypad interfacing session.

