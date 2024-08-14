#include "../lib/HRRN.h"
#include <stdio.h>

static queue_object* HRRN_queue;

/**
 * Print queue (used for debugging).
 * @param queue - contains all processes of type HRRN_process
*/
void HRRN_print_queue(queue_object *queue) {
    if (queue == NULL) {
        return;
    }
    printf("\nHEAD->");
    if (queue->next == NULL) { // queue is empty (only head)
        return;
    }
    queue_object *tmp_element = queue->next;
    HRRN_process *tmp_HRRN;
    while (tmp_element != NULL) { // iterate over all queue elements
        tmp_HRRN = tmp_element->object;
        printf("%c->", tmp_HRRN->this_process->id);
        tmp_element = tmp_element->next;
    }
}

/**
 * Calculates the rr-value of a process.
 * @param process - a process of type HRRN_process
*/
float calc_rr(HRRN_process *process) {
    float waiting_time = process->waiting_time;
    float running_time = process->this_process->time_left;
    if (running_time == 0) {
        return -1.0;
    }
    return (waiting_time + running_time) / running_time;
}

/**
 * Updates the rr-value of all processes.
 * @param queue - contains all processes of type HRRN_process
*/
void update_rr_value(queue_object *queue) {
    if (queue == NULL) {
        return;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return;
    }
    queue_object *tmp_element = queue->next;
    HRRN_process *tmp_HRRN;
    while (tmp_element != NULL) { // iterate over all queue elements
        tmp_HRRN = tmp_element->object;
        tmp_HRRN->rr = calc_rr(tmp_HRRN);
        tmp_element = tmp_element->next;
    }
}

/**
 * Inkrement the waiting time of all processes except of the currently
 * running prozess.
 * @param queue - contains all processes of type HRRN_process
 * @param running_process - the currently running proxess
*/
void inkrement_waiting_time(queue_object *queue, process *running_process) {
    if (queue == NULL) {
        return;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return;
    }
    queue_object *tmp_element = queue->next;
    HRRN_process *tmp_HRRN;
    while (tmp_element != NULL) { // iterate over all queue elements
        tmp_HRRN = tmp_element->object;
        if (tmp_HRRN->this_process != running_process) {
            tmp_HRRN->waiting_time++;
        }
        tmp_element = tmp_element->next;
    }
}

/**
 * Rearanges the queue elements so that the prozess with the highest
 * rr-value can be polled/peeked next.
 * @param queue - contains all processes of type HRRN_process
*/
void rearange_queue(queue_object *queue) {
    if (queue == NULL) {
        return;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return;
    }
    update_rr_value(queue);
    queue_object *tmp_element = queue->next;
    queue_object *tmp_prev_element = queue;
    HRRN_process *tmp_HRRN = tmp_element->object;
    float max_rr = tmp_HRRN->rr;
    while (tmp_element != NULL) { // iterate over all queue elements
        tmp_HRRN = tmp_element->object;
        if (tmp_HRRN->rr < max_rr) {
            queue_object *tmp = tmp_element->next;
            tmp_prev_element->next = tmp_element->next;
            HRRN_process *new_HRRN = calloc(1, sizeof(HRRN_process));
            if (new_HRRN == NULL) {
                printf("calloc returned NULL. Unexpected!\n");
            }
            new_HRRN->this_process = tmp_HRRN->this_process;
            new_HRRN->waiting_time = tmp_HRRN->waiting_time;
            new_HRRN->rr = tmp_HRRN->rr;
            queue_add(new_HRRN, HRRN_queue);
            free(tmp_HRRN);
            free(tmp_element);
            tmp_element = tmp;
        } else {
            max_rr = tmp_HRRN->rr;
            tmp_prev_element = tmp_element;
            tmp_element = tmp_element->next;
        }
    }
}

process* HRRN_tick (process* running_process){
    rearange_queue(HRRN_queue);
    //HRRN_print_queue(HRRN_queue);
    if (running_process == NULL || running_process->time_left == 0) {
        HRRN_process *new_HRRN = queue_poll(HRRN_queue);
        if (new_HRRN != NULL) {
            running_process = new_HRRN->this_process;
            free(new_HRRN);
        } else {
            running_process = NULL;
        }
    }
    if (running_process != NULL) {
        running_process->time_left--;
    }
    inkrement_waiting_time(HRRN_queue, running_process);
    return running_process;
}

int HRRN_startup(){
    HRRN_queue = new_queue();
    if (HRRN_queue == NULL) {
        return 1;
    }
    return 0;
}

process* HRRN_new_arrival(process* arriving_process, process* running_process){
    if (arriving_process != NULL) {
        HRRN_process *new_HRRN = calloc(1, sizeof(HRRN_process));
        if (new_HRRN == NULL) {
            printf("calloc returned NULL. Unexpected!\n");
        }
        new_HRRN->this_process = arriving_process;
        new_HRRN->waiting_time = 0;
        new_HRRN->rr = 0;
        queue_add(new_HRRN, HRRN_queue);
    }
    return running_process;
}

void HRRN_finish(){
    free_queue(HRRN_queue);
}
