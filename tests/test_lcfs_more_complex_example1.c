#include"../lib/scheduler.h"
#include"../lib/process.h"
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

#define PROCESS_COUNT   10
#define RR_QUANTUM      2
#define STRATEGY        LCFS

int main()
{
    fprintf(stderr, "This is a more complex test for LCFS.");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Check how you poll LCFS_queue. It doesn't behave like a STACK\n"
            "\t- If still not found: Happy debbugging!\n");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{   0,      3,      1,      'A'},
                                        {   1,      3,      4,      'B'},
                                        {   2,      5,      4,      'C'},
                                        {   4,      2,      4,      'O'},
                                        {   6,      1,      4,      'G'},
                                        {   10,     1,      4,      'D'},
                                        {   12,     2,      4,      'S'},
                                        {   14,     3,      4,      'T'},
                                        {   16,     1,      4,      'F'},
                                        {   17,     3,      2,      'M'}};

    
    char* expected_result = "AAACCCCCGOODSSTTTMMMFBBB";

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
