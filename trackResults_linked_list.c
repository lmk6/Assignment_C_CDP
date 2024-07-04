//
// Created by lmk6 on 08/01/2022.
//

#include <malloc.h>
#include "trackResults_linked_list.h"

/**
 * result constructor
 * @param compNum competitor number
 * @param m minutes
 * @param s seconds
 * @param ms milliseconds
 * @return return pointer to new result
 */
result_pointer createNewResult(int compNum, int m, int s, int ms) {
    result_pointer new_result;
    new_result = malloc(sizeof(result));
    if (new_result == NULL) return NULL;
    new_result->competitor_num = compNum;
    new_result->minutes = m;
    new_result->seconds = s;
    new_result->milliseconds = ms;
    new_result->next = NULL;
    return new_result;
}

/**
 * Inserts new result to the list
 * @param ptr_to_head head reference
 * @param new_ptr new result
 */
void insertAtTopOfResultsList(result_pointer *ptr_to_head, result_pointer new_ptr) {
    new_ptr->next = *ptr_to_head;
    *ptr_to_head = new_ptr;
}

/**
 * Function called to completely clear the list's
 * contents from memory
 * @param head_ref pointer to the top of the list
 */
void clearListOfResults(result_pointer *head_ref) {
    result_pointer current = *head_ref;
    result_pointer next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

/**
 * Alternative result constructor, creates result with all
 * values equal to zero
 * @param compNum competitor number
 * @return 'empty' result
 */
result_pointer getEmptyResult(int compNum) {
    result_pointer empty_res = createNewResult(compNum, 0, 0, 0);
    if (empty_res == NULL) return NULL;
    return empty_res;
}