#include "../lib/MLF.h"
#include <stdio.h>

static queue_object** MLF_queues;
static const int n = 4; // total number of levels
static const int quantum[4] = {1, 3, 9, -1}; // last level has 'unlimited' quantum
static int current_quantum;
static int current_lvl;

/**
 * Print queue (used for debugging).
 * @param queue - contains all processes
*/
void MLF_print_queue(queue_object *queue) {
    if (queue == NULL) {
        return;
    }
    printf("\nHEAD->");
    if (queue->next == NULL) { // queue is empty (only head)
        return;
    }
    queue_object *tmp_element = queue->next;
    process *tmp_process;
    while (tmp_element != NULL) { // iterate over all queue elements
        tmp_process = tmp_element->object;
        printf("%c->", tmp_process->id);
        tmp_element = tmp_element->next;
    }
}

process* MLF_tick (process* running_process){
    if (running_process == NULL || quantum[current_lvl] - current_quantum == 0 || running_process->time_left == 0) {
        if (running_process != NULL) {
            if (running_process->time_left == 0) {
                queue_poll(MLF_queues[current_lvl]);
            } else if (quantum[current_lvl] - current_quantum == 0) {
                /* Level 3 (last level) never gets into this if-block
                 * because quantum[3] = -1 and current_quantum is always >= 0 */
                process *tmp = queue_poll(MLF_queues[current_lvl]);
                queue_add(tmp, MLF_queues[current_lvl+1]);
            }
        }
        for (int i = 0; i < n; i++) { // iterate over lvl's to find next process
            running_process = queue_peek(MLF_queues[i]);
            if (running_process != NULL) {
                current_lvl = i;
                current_quantum = 0;
                break;
            }
        }
    }
    if (running_process != NULL){
        running_process->time_left--;
        current_quantum++;
    }
    return running_process;
}

int MLF_startup(){
    MLF_queues = calloc(n, sizeof(queue_object));
    if (MLF_queues == NULL){
        return 1;
    }
    for (int i = 0; i < n; i++) {
        MLF_queues[i] = new_queue();
        if (MLF_queues[i] == NULL){
            return 1;
        }
    }
    current_lvl = 0;
    current_quantum = 0;
    return 0;
}

process* MLF_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process != NULL){
        queue_add(arriving_process, MLF_queues[0]);
    }
    return running_process;
}

void MLF_finish(){
    for (int i = 0; i < n; i++) {
        free_queue(MLF_queues[i]);
    }
    free(MLF_queues);
}
