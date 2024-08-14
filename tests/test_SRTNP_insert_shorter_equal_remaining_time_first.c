#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM      2
#define STRATEGY        SRTNP

int main()
{
    fprintf(stderr, "Tests the pre-emption.");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Is it possible to preempt when the arriving_process has \n"
            "\t  a shorter remaining time?"
            "\t- If a process finished, so you choose the process with the \n"
            "\t  shortest remaining time to run next?"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      2,      9,      'A'},
                                        {    1,      1,      8,      'B'},
                                        {    2,      7,      7,      'C'},
                                        {    3,      6,      6,      'Z'}};
    
    char* expected_result = "AABZZZZZZCCCCCCC";

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result,resulting_schedule)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result,resulting_schedule);
        free(resulting_schedule);
        exit(1);
    }
    printf("Passed.\n");

    free(resulting_schedule);
    exit(0);
}
