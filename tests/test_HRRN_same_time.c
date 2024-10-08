#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        HRRN

int main()
{
    fprintf(stderr, "Tests calculation of RR");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Take a look at how you HRRN_queue chooses the next item\n"
            "\t- Take a look at when you calculate/update RR\n"
            "\t- Take a look at how yoiu calculate/update RR\n"
            "\t- If not: Happy debugging!");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      4,      1,      'A'},
                                        {    1,      2,      1,      'B'},
                                        {    2,      2,      7,      'Y'},
                                        {    3,      2,      7,      'Z'},
                                        {    4,      2,      1,      'T'}};

    char* expected_result = "AAAABBYYZZTT";

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
