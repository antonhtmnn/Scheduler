#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   4
#define RR_QUANTUM       2
#define STRATEGY         PRIOP

int main()
{
    fprintf(stderr, "Checks correct initialization of variables.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Check how you initialize your variables that you declare on top of PRIOP.c!\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes1[PROCESS_COUNT] = {{   0,      3,      4,      'U'},
                                        {    1,      4,      2,      'W'},
                                        {    2,      5,      2,      'E'},
                                        {    3,      2,      1,      'N'}};
    
    char* expected_result1 = "UUUWWWWEEEEENN";

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
    process processes2[PROCESS_COUNT] = {{    0,      3,      1,      'U'},
                                        {    1,      4,      2,      'W'},
                                        {    2,      5,      3,      'E'},
                                        {    3,      2,      4,      'N'}};
    
    char* expected_result2 = "UWENNEEEEWWWUU";

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
