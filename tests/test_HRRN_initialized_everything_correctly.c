#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT1  3
#define PROCESS_COUNT2  5
#define RR_QUANTUM      2
#define STRATEGY        HRRN

int main()
{
    fprintf(stderr, "Checks correct initialization of variables.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Check how you initialize your variables that you declare on top of HRRN.c!\n"
            "\t- If still not found: Happy debugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes1[PROCESS_COUNT1] = {{   0,      3,      1,      'A'},
                                        {    1,      2,      4,      'B'},
                                        {    2,      2,      2,      'C'}};

    
    char* expected_result1 = "AAABBCC";

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
    process processes2[PROCESS_COUNT2] = {{  0,      7,      8,      'A'},
                                        {    1,      1,      9,      'B'},
                                        {    2,      3,      7,      'C'},
                                        {    3,      5,      1,      'G'},
                                        {    4,      7,      1,      'E'}};

    char* expected_result2 = "AAAAAAABCCCGGGGGEEEEEEE";

    char* resulting_schedule2 = scheduler(processes2,PROCESS_COUNT2,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result2,resulting_schedule2)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result2,resulting_schedule2);
        free(resulting_schedule2);
        exit(1);
    }
    printf("Passed.\n");

    free(resulting_schedule2);
    exit(0);
}
