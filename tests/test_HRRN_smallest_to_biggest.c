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
    fprintf(stderr, "Tests correct order when going from smallest to biggest.");
    fprintf(stderr, "If doesn't pass:\n"
            "\t- Take a look at how your queue chooses the next item.\n"
            "\t- How is your RR calculated? Did you forget to cast to float?\n"
            "\t- When is your RR calculated? Do you forgot to update the values at a crucial point?\n"
            "\t- If not: Happy debugging!");
    /*Defining the processes                Arrival Dur.    Prio    ID
                                            uint    uint    uint    char*/
    process processes[PROCESS_COUNT] = {{    0,      7,      8,      'A'},
                                        {    1,      1,      9,      'B'},
                                        {    2,      3,      7,      'C'},
                                        {    3,      5,      1,      'G'},
                                        {    4,      7,      1,      'E'}};

    char* expected_result = "AAAAAAABCCCGGGGGEEEEEEE";

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
