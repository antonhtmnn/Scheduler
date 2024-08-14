#include "../lib/queue.h"
#include <stdlib.h>
#include <stdio.h>

int queue_add(void* new_obejct, queue_object* queue){
    if (new_obejct == NULL || queue == NULL) {
        return 1;
    }
    queue_object *new_element = calloc(1, sizeof(queue_object));
    if (new_element == NULL) {
        return 1;
    }
    new_element->object = new_obejct;
    new_element->next = queue->next;
    queue->next = new_element;
    return 0;
}

void* queue_poll(queue_object* queue){
    if (queue == NULL) {
        return NULL;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return NULL;
    }
    queue_object *tmp_element = queue->next;
    queue_object *tmp_previous_element = queue;
    while (tmp_element->next != NULL) { // iterate to last queue element
        tmp_previous_element = tmp_element;
        tmp_element = tmp_element->next;
    }
    void *oldest_object = tmp_element->object; // store return value
    tmp_previous_element->next = NULL; // new oldest-element
    free(tmp_element);
    return oldest_object;
}

queue_object* new_queue(){
    queue_object *queue = calloc(1, sizeof(queue_object));
    if (queue == NULL) {
        printf("calloc returned NULL. Unexpected!\n");
    }
    return queue;
}

void free_queue(queue_object* queue){
    if (queue == NULL) {
        return;
    }
    /* Because of our 'queue_add()' implementation we know that only
    the head element can have a NULL object. */
    void *current_object = queue_poll(queue);
    while (current_object != NULL) {
        current_object = queue_poll(queue);
    }
    free(queue);
}

void* queue_peek(queue_object* queue){
    if (queue == NULL) {
        return NULL;
    }
    if (queue->next == NULL) { // queue is empty (only head)
        return NULL;
    }
    queue_object *tmp_element = queue->next;
    while (tmp_element->next != NULL) { // iterate to last queue element
        tmp_element = tmp_element->next;
    }
    return tmp_element->object;
}
