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
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes1[PROCESS_COUNT] = {{   0,      7,      9,      'A'},
                                        {    1,      5,      8,      'B'},
                                        {    2,      3,      7,      'C'},
                                        {    3,      1,      6,      'Z'}};

    
    char* expected_result1 = "ABCZCCBBBBAAAAAA";

    char* resulting_schedule1 = scheduler(processes1,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result1,resulting_schedule1)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result1,resulting_schedule1);
        free(resulting_schedule1);
        exit(1);
    }
    printf("Passed first one.\n");

    free(resulting_schedule1);

    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes2[PROCESS_COUNT] = {{   0,      2,      9,      'A'},
                                        {    1,      1,      8,      'B'},
                                        {    2,      7,      7,      'C'},
                                        {    3,      6,      6,      'Z'}};
    
    char* expected_result2 = "AABZZZZZZCCCCCCC";

    char* resulting_schedule2 = scheduler(processes2,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result2,resulting_schedule2)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result2,resulting_schedule2);
        free(resulting_schedule2);
        exit(1);
    }
    printf("Passed second one.\n");

    free(resulting_schedule2);
    exit(0);
}
