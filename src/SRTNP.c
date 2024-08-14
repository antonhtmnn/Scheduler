#include "../lib/SRTNP.h"

static queue_object* SRTNP_queue;

/**
 * Gets (returns) the prozess with the lowest remaining time left (!= 0).
 * @param queue - contains all processes
*/
process *SRTNP_get_process(queue_object *queue) {
    if (queue == NULL) {
        return NULL;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return NULL;
    }
    queue_object *tmp_element = queue->next;
    queue_object *tmp_min = NULL;
    int min = 9999;
    while (tmp_element != NULL) {
        int current_min = ((process *)(tmp_element->object))->time_left;
        if (current_min != 0 && current_min <= min) {
            tmp_min = tmp_element;
            min = current_min;

        }
        tmp_element = tmp_element->next;
    }
    if (tmp_min == NULL) {
        return NULL;
    }
    return tmp_min->object;
}

process* SRTNP_tick (process* running_process){
    running_process = SRTNP_get_process(SRTNP_queue);
    if (running_process != NULL) {
        running_process->time_left--;
    }
    return running_process;
}

int SRTNP_startup(){
    SRTNP_queue = new_queue();
    if (SRTNP_queue == NULL){
        return 1;
    }
    return 0;
}

process* SRTNP_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process != NULL) {
        queue_add(arriving_process, SRTNP_queue);
    }
    running_process = SRTNP_get_process(SRTNP_queue);
    return running_process;
}

void SRTNP_finish(){
    free_queue(SRTNP_queue);
}
