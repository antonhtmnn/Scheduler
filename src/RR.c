#include "../lib/RR.h"

static queue_object* RR_queue;
static int RR_quantum; // stores the provided quantum at startup
static int time; // used to check if the quantum limit is reached

process* RR_tick (process* running_process){
    if (running_process == NULL) {
        running_process = queue_peek(RR_queue);
    } else {
        if (running_process->time_left == 0) {
            queue_poll(RR_queue);
            running_process = queue_peek(RR_queue);
            time = 0; // reset time -> new cycle
        } else if (time % RR_quantum == 0) { // quantum limit is reached
            process *tmp = queue_poll(RR_queue);
            queue_add(tmp, RR_queue);
            running_process = queue_peek(RR_queue);
        }
    }
    if (running_process != NULL) {
        running_process->time_left--;
        time++;
    }
    return running_process;
}

int RR_startup(int quantum){
    RR_queue = new_queue();
    if (RR_queue == NULL){
        return 1;
    }
    RR_quantum = quantum;
    time = 0;
    return 0;
}

process* RR_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process != NULL){
        queue_add(arriving_process, RR_queue);
    }
    return running_process;
}

void RR_finish(){
    free_queue(RR_queue);
}
