#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   3
#define RR_QUANTUM      2
#define STRATEGY        MLF

int main()
{
    fprintf(stderr, "Tests for period where nothing is run.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Did you look for NULL values?\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   1,      2,      6,      'A'},
                                        {   5,      5,      4,      'B'},
                                        {   8,      1,      2,      'C'}};

    
    char* expected_result = " AA  BBBBCB";

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
