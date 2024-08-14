#include "../lib/LCFS.h"
#include <stdio.h>

static queue_object* LCFS_queue;

int LCFS_startup(){
    LCFS_queue = new_queue();
    if (LCFS_queue == NULL){
        return 1;
    }
    return 0;
}

/**
 * Polls the newest (most recently added) element of the queue -> lcfs order
 * without having to rearange the queue elements.
 * @param queue - contains all processes
*/
void *queue_poll_newest(queue_object *queue) {
    if (queue == NULL) {
        return NULL;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return NULL;
    }
    queue_object *newest_element = queue->next;
    void *newest_object = newest_element->object; // store return value
    queue->next = newest_element->next;
    free(newest_element);
    return newest_object;
}

process* LCFS_tick(process* running_process){
    if (running_process == NULL || running_process->time_left == 0){
        running_process = queue_poll_newest(LCFS_queue);
    }
    if (running_process != NULL){
        running_process->time_left--;
    }
    return running_process;
}

process* LCFS_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process != NULL){
        queue_add(arriving_process, LCFS_queue);
    }
    return running_process;
}

void LCFS_finish(){
    free_queue(LCFS_queue);
}
