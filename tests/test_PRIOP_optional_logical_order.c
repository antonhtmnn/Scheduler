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
    fprintf(stderr, "\n\nThis is optional, because it hasn't been 'officially' said.\n"
            "I would recommend to code your algorithm to pass this test tho. \n"
            "This test checks the following case:\n"
            "If you have two processes with the same priority, the OLDER one should be chosen first.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- When choosing from in queue you might need to add a '='. \n "
            "\t->Try it out and if it passes this test then your order is 'more logical'\n"
            "\t- If not: Ask whether you have to do it. If not just delete this test!\n\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      5,      1,      'A'},
                                        {    1,      2,      1,      'B'},
                                        {    2,      2,      1,      'C'},
                                        {    4,      2,      1,      'Z'}};
    
    char* expected_result = "AAAAABBCCZZ";

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
