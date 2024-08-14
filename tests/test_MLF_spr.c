#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      3
#define STRATEGY        MLF

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {{   0,      6,      2,      'A'},
                                      {   8,      14,      4,      'B'},
                                      {   16,      9,      1,      'C'},
                                      {   21,      13,      5,      'D'},
                                      {   37,      8,      3,      'E'}};

    
    char* expected_result = "AAAAAA  BBBBBBBBBBBBBCDCCCDDDCCCCCDDDDDDDDDEEEEEEEEB";

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
