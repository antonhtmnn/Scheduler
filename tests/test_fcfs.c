#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        FCFS

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,       6,      2,      'A'},
                                        {    8,      14,      1,      'B'},
                                        {   16,       9,      5,      'C'},
                                        {   21,      13,      4,      'D'},
                                        {   37,       8,      3,      'E'}};


    char* expected_result = "AAAAAA  BBBBBBBBBBBBBBCCCCCCCCCDDDDDDDDDDDDDEEEEEEEE";

    char* resulting_schedule = scheduler(processes,PROCESS_COUNT,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result,resulting_schedule)){
        printf("Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result,resulting_schedule);
        free(resulting_schedule);
        exit(1);
    }
    printf("Passed.\n");

    free(resulting_schedule);
    exit(0);
}
