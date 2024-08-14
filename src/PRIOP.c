#include "../lib/PRIOP.h"
#include <stdio.h>

static queue_object* PRIOP_queue;

/**
 * Rearanges the queue elements so that the prozess with the highest
 * priority can be polled/peeked next.
 * @param queue - contains all processes
*/
void PRIOP_rearange_queue(queue_object *queue) {
    if (queue == NULL) {
        return;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return;
    }
    queue_object *tmp_element = queue->next;
    queue_object *tmp_prev_element = queue;
    process *tmp_process = tmp_element->object;
    unsigned int max_prio = tmp_process->priority;
    while (tmp_element != NULL) { // iterate over all queue elements
        tmp_process = tmp_element->object;
        if (tmp_process->priority < max_prio) {
            queue_object *tmp = tmp_element->next;
            tmp_prev_element->next = tmp_element->next;
            queue_add(tmp_process, PRIOP_queue);
            free(tmp_element);
            tmp_element = tmp;
        } else {
            max_prio = tmp_process->priority;
            tmp_prev_element = tmp_element;
            tmp_element = tmp_element->next;
        }
    }
}

process* PRIOP_tick (process* running_process){
    if (running_process == NULL) {
        PRIOP_rearange_queue(PRIOP_queue);
        running_process = queue_peek(PRIOP_queue);
    }
    if (running_process != NULL && running_process->time_left == 0) {
        queue_poll(PRIOP_queue);
        PRIOP_rearange_queue(PRIOP_queue);
        running_process = queue_peek(PRIOP_queue);
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }
    return running_process;
}

int PRIOP_startup(){
    PRIOP_queue = new_queue();
    if (PRIOP_queue == NULL){
        return 1;
    }
    return 0;
}

process* PRIOP_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process != NULL) {
        queue_add(arriving_process, PRIOP_queue);
        if (running_process != NULL && (arriving_process->priority > running_process->priority)) {
            PRIOP_rearange_queue(PRIOP_queue);
            running_process = queue_peek(PRIOP_queue);
        }
    }
    return running_process;
}

void PRIOP_finish(){
    free_queue(PRIOP_queue);
}
