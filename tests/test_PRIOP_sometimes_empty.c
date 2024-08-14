#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM      2
#define STRATEGY        PRIOP

int main()
{
    fprintf(stderr, "Tests what happens when nothing gets run.");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Did you forget to check for NULL?\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    1,      3,      3,      'A'},
                                        {    2,      2,      9,      'B'},
                                        {    10,     3,      4,      'C'},
                                        {    12,     2,      9,      'Z'}};
    
    char* expected_result = " ABBAA    CCZZC";

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
