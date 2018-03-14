/* 
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    /* Remember to handle the case if malloc returned NULL */
    queue_t *queue_new; 
    if (NULL == (queue_new = (queue_t *) malloc(sizeof(queue_t)))) {
        return NULL;
    }
    queue_new -> head = NULL;
    queue_new -> tail = NULL;
    queue_new -> size = 0;

    return queue_new;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* Remember to free the queue structue and list elements */
    if (NULL == q) {
        return;
    }
    list_ele_t *temp_head, *temp_del;

    temp_head = q -> head;
    while (temp_head != NULL) {
        temp_del = temp_head;
        temp_head = temp_head -> next;
        free(temp_del);
    }
    free(q);
    q = NULL;
    return;
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_head(queue_t *q, int v)
{
    /* What should you do if the q is NULL? */
    /* What if malloc returned NULL? */
    list_ele_t *temp_list, *temp_head;
    if (NULL == q || NULL == (temp_list = (list_ele_t *) malloc(sizeof(list_ele_t)))) {
        return false;
    }
    temp_list -> value = v;
    //if (q -> head == NULL) {
    //    q -> head = temp_list;
    //    q -> tail = q -> head;
    //    return true;
    //}
    temp_head = q -> head;
    q -> head = temp_list;
    if (NULL == q -> tail) {
        q -> tail = temp_list;
    }
    temp_list -> next = temp_head;
    q -> size ++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
 */
bool q_insert_tail(queue_t *q, int v)
{
    /* Remember: It should operate in O(1) time */
    list_ele_t *temp_list, *temp_tail;
    if (NULL == q || NULL == (temp_list = (list_ele_t *)malloc(sizeof(list_ele_t)))) {
        return false;    
    }
    temp_list -> value = v;
    temp_list -> next = NULL;
    temp_tail = q -> tail;
    q -> tail = temp_list;
    if (NULL == q -> head) {
        q -> head = temp_list;
        q -> size ++;
        return true;    
    }
    temp_tail -> next = temp_list;
    q -> size ++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If vp non-NULL and element removed, store removed value at *vp.
  Any unused storage should be freed
*/
bool q_remove_head(queue_t *q, int *vp)
{
    if (NULL == q || NULL == q -> head || NULL == vp) {
        return false;
    }
    if (q -> head == q -> tail) {
        *vp = q -> head -> value;
        free(q -> head);
        q -> head = NULL;
        q -> tail = NULL;
        q -> size = 0;
        return true;
    }

    list_ele_t * temp_list = q -> head;
    q -> head = q -> head -> next;
    *vp = temp_list -> value;
    q -> size --;
    free(temp_list);
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* Remember: It should operate in O(1) time */
    if (NULL == q || NULL == q -> head) {
        return 0;
    }
    else return q -> size;
}

/*
  Reverse elements in queue.

  Your implementation must not allocate or free any elements (e.g., by
  calling q_insert_head or q_remove_head).  Instead, it should modify
  the pointers in the existing data structure.
 */
void q_reverse(queue_t *q)
{
    if (NULL == q || NULL == q -> head || q -> head == q -> tail)
        return;
    list_ele_t * pointer1 = q -> head;
    list_ele_t * pointer2 = q -> head -> next;
    q -> head -> next = NULL;
    list_ele_t * temp_pointer;
    while (pointer2 != NULL) {
        temp_pointer = pointer2 -> next;
        pointer2 -> next = pointer1;
        pointer1 = pointer2;
        pointer2 = temp_pointer;        
    }
    // swap head and tail
    temp_pointer = q -> head;
    q -> head = q -> tail;
    q -> tail = temp_pointer;
    return;
}

