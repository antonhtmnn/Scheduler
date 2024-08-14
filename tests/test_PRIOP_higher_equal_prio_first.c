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
    fprintf(stderr, "Tests the pre-emption.");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Take a look at how you choose the processes when they arrive.\n"
            "\t- Take a look at how you choose the processes when one process finished.\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      3,      4,      'U'},
                                        {    1,      4,      2,      'W'},
                                        {    2,      5,      2,      'E'},
                                        {    3,      2,      1,      'N'}};
    
    char* expected_result = "UUUWWWWEEEEENN";

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
