#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT1   5
#define PROCESS_COUNT2   10
#define RR_QUANTUM      2
#define STRATEGY        LCFS

// I know that my implementation is not clean, but I just lazily pasted it in!!!
// This doesn't make debugging this code harder tho!!!
int main()
{
    fprintf(stderr, "Checks correct initialization of variables.\n");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Check how you initialize your variables that you declare on top of LCFS.c!\n"
            "\t- If still not found: Happy debugging!\n");

    // first process
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes1[PROCESS_COUNT1] = {{   1,      2,      1,      'A'},
                                         {    5,      1,      4,      'M'},
                                         {    7,      3,      9,      'C'},
                                         {    11,     4,      100,    'D'},
                                         {    15,     3,      2,      'Z'}};

    
    char* expected_result1 = " AA  M CCC DDDDZZZ";

    char* resulting_schedule1 = scheduler(processes1,PROCESS_COUNT1,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result1,resulting_schedule1)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result1,resulting_schedule1);
        free(resulting_schedule1);
        exit(1);
    }
    printf("Passed first one.\n");

    free(resulting_schedule1);

    // second process
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT2] = {{   0,      3,      1,      'A'},
                                        {    1,      3,      4,      'B'},
                                        {    2,      5,      4,      'C'},
                                        {    4,      2,      4,      'O'},
                                        {    6,      1,      4,      'G'},
                                        {    10,     1,      4,      'D'},
                                        {    12,     2,      4,      'S'},
                                        {    14,     3,      4,      'T'},
                                        {    16,     1,      4,      'F'},
                                        {    17,     3,      2,      'M'}};

    
    char* expected_result2 = "AAACCCCCGOODSSTTTMMMFBBB";

    char* resulting_schedule2 = scheduler(processes,PROCESS_COUNT2,STRATEGY,RR_QUANTUM);

    if(strcmp(expected_result2,resulting_schedule2)){
        fprintf(stderr, "Wrong.\nExpected: \n%s\nGot:\n%s\n",expected_result2,resulting_schedule2);
        free(resulting_schedule2);
        exit(1);
    }
    printf("Passed second one.\n");

    free(resulting_schedule2);

    exit(0);
}
