//
// Created by lmk6 on 07/01/2022.
//
#include "trackResults_linked_list.h"
#include "tracks_linked_list.h"
#ifndef ASSIGNMENT_C_CDP_COMPETITORS_LINKED_LIST_H
#define ASSIGNMENT_C_CDP_COMPETITORS_LINKED_LIST_H
//global variable
static int number_of_competitors;

//returning global variable's value
int getNum_of_competitors();

//resetting global value to 0
void reset_num_of_competitors();

//competitor struct and its pointer
typedef struct competitor_tag *competitor_pointer;
void newCompetitor();
typedef struct competitor_tag {
    char *family_name;
    char *name;
    int competitor_number;
    result_pointer result_list_head;
    competitor_pointer next;
} competitor;

//competitor constructor
competitor_pointer createNewCompetitor(char *fName, char *name,  int competitorN);

//list manipulating functions
void insertAtTop(competitor_pointer *ptr_to_head, competitor_pointer new_ptr);
void clearList(competitor_pointer *head_ref);
int giveCompetitorTheResults(competitor_pointer *head, track_pointer *track_list_head);
void clearAllResults(competitor_pointer *head);

//Modifying list element's list
void addResultToCompetitor(competitor_pointer *ptr_to_comp, result_pointer result);

//comparison function
int compareTotalTimes(const void *first, const void *second);
#endif //ASSIGNMENT_C_CDP_COMPETITORS_LINKED_LIST_H
