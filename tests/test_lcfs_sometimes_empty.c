#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        LCFS

int main()
{
    fprintf(stderr, "Checks behaviour with empty slots.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- check polling of LCFS_queue!\n"
            "\t- did you forget to check for NULL somewhere?\n"
            "\t- If not: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   1,      2,      1,      'A'},
                                        {   5,      1,      4,      'M'},
                                        {   7,      3,      9,      'C'},
                                        {   11,     4,      100,    'D'},
                                        {   15,     3,      2,      'Z'}};

    
    char* expected_result = " AA  M CCC DDDDZZZ";

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
