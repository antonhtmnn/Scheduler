#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT1   7
#define PROCESS_COUNT2   3
#define RR_QUANTUM       2
#define STRATEGY         MLF

int main()
{
    fprintf(stderr, "Checks correct initialization of variables.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Check how you initialize your variables that you declare on top of MLF.c!\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes1[PROCESS_COUNT1] = {{  0,      30,     6,      'A'},
                                        {    7,      42,     4,      'B'},
                                        {    20,     5,      1,      'C'},
                                        {    32,     70,     9,      'D'},
                                        {    40,     13,     4,      'E'},
                                        {    52,     1,      3,      'F'},
                                        {    60,     4,      2,      'G'}};

    char* expected_result1 = "AAAAAAAAAAAAABBBBBBBBBBBBBCCCCCAAAAAAAAAAAAAAAAADEDDDFEEEDDDDDDDDDGGGGEEEEEEEEEBBBBBBBBBBBBBBBBBBBBBBBBBBBBBDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDDD";

    char* resulting_schedule1 = scheduler(processes1,PROCESS_COUNT1,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result1,resulting_schedule1)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result1,resulting_schedule1);
        free(resulting_schedule1);
        exit(1);
    }
    printf("Passed first one.\n");

    free(resulting_schedule1);

    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes2[PROCESS_COUNT2] = {{  1,      2,      6,      'A'},
                                        {    5,      5,      4,      'B'},
                                        {    8,      1,      2,      'C'}};

    
    char* expected_result2 = " AA  BBBBCB";

    char* resulting_schedule2 = scheduler(processes2,PROCESS_COUNT2,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result2,resulting_schedule2)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result2,resulting_schedule2);
        free(resulting_schedule2);
        exit(1);
    }
    printf("Passed second one.\n");

    free(resulting_schedule2);
    exit(0);
}
