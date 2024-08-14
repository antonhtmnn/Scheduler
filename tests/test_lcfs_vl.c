#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   5
#define RR_QUANTUM      2
#define STRATEGY        LCFS

int main()
{
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
  process processes[PROCESS_COUNT] = {{   0,      3,      2,      'A'},
                                      {   2,      6,      4,      'B'},
                                      {   4,      4,      1,      'C'},
                                      {   6,      5,      5,      'D'},
                                      {   8,      2,      3,      'E'}};


  char* expected_result = "AAABBBBBBEEDDDDDCCCC";

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
