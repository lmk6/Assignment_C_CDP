//
// Created by 48505 on 08/01/2022.
//

#ifndef ASSIGNMENT_C_CDP_TRACKRESULTS_LINKED_LIST_H
#define ASSIGNMENT_C_CDP_TRACKRESULTS_LINKED_LIST_H

//Result struct and its pointer
typedef struct result_tag *result_pointer;
typedef struct result_tag {
    int competitor_num;
    int minutes;
    int seconds;
    int milliseconds;
    result_pointer next;
} result;

//Result constructor
result_pointer createNewResult(int competitor_number, int minutes,
                              int seconds, int milliseconds);

//Inserting new element to the list
void insertAtTopOfResultsList(result_pointer *ptr_to_head, result_pointer new_ptr);

//List destructor
void clearListOfResults(result_pointer *head_ref);

#endif //ASSIGNMENT_C_CDP_TRACKRESULTS_LINKED_LIST_H
