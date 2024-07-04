//
// Created by lmk6 on 07/01/2022.
//

#include "competitors_linked_list.h"
#include <malloc.h>
#include <string.h>

/**
 * resets recorded number of competitors
 */
void reset_num_of_competitors() {
    number_of_competitors = 0;
}

/**
 * @return recorded number of competitors
 */
int getNum_of_competitors() {
    return number_of_competitors;
}

/**
 * function used to create new competitor
 * @param fName family name
 * @param name name
 * @param competitorN competitor number
 * @param result_list_head list of results
 * @param next link to next competitor
 * @return pointer to newly created competitor
 */
competitor_pointer createNewCompetitor(char *fName, char *name, int competitorN) {
    competitor_pointer new_competitor;
    new_competitor = malloc(sizeof(competitor));
    if (new_competitor == NULL) return NULL;
    new_competitor->family_name = malloc(strlen(fName) + 1);
    new_competitor->name = malloc(strlen(name) + 1);
    new_competitor->name = strdup(name);
    new_competitor->family_name = strdup(fName);
    new_competitor->competitor_number = competitorN;
    new_competitor->result_list_head = NULL;
    new_competitor->next = NULL;
    number_of_competitors++;
    return new_competitor;
}

/**
 * Function inserting new competitor at the top of the list
 * @param ptr_to_head head reference
 * @param new_ptr pointer to new competitor
 */
void insertAtTop(competitor_pointer *ptr_to_head, competitor_pointer new_ptr) {
    new_ptr->next = *ptr_to_head;
    *ptr_to_head = new_ptr;
}

/**
 * Inserts result to competitor's list of results
 * @param ptr_to_comp reference to competitor
 * @param result result to insert
 */
void addResultToCompetitor(competitor_pointer *ptr_to_comp, result_pointer result) {
    competitor_pointer comp = *ptr_to_comp;
    if (comp != NULL && result != NULL &&
        result->competitor_num == comp->competitor_number) {       //last statement just for safety
        insertAtTopOfResultsList(&(comp->result_list_head), result);
    }
}

/**
 * Function called to completely clear the list's
 * contents from memory
 * @param head_ref reference to head of the list
 */
void clearList(competitor_pointer *head_ref) {
    competitor_pointer current = *head_ref;
    competitor_pointer next;
    while (current != NULL) {
        next = current->next;
        free(current->family_name);
        free(current->name);
        clearListOfResults(&(current->result_list_head));
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

/**
 * Removes all results of all competitors
 * @param head head reference to competitor list
 */
void clearAllResults(competitor_pointer *head) {
    competitor_pointer next = *head;
    result_pointer res_ref;
    while(next != NULL) {
        res_ref = next->result_list_head;
        clearListOfResults(&res_ref);
        next->result_list_head = NULL;
        next = next->next;
    }
}

/**
 * Comparison function
 * Compares two competitors by their total time
 * @param first competitor
 * @param second competitor
 * @return result of comparison
 */
int compareTotalTimes(const void *first, const void *second) {
    competitor_pointer competitor1;
    competitor1 = (competitor_pointer) first;
    competitor_pointer competitor2;
    competitor2 = (competitor_pointer) second;
    int competitor1val = 0;
    int competitor2val = 0;
    //counts number of tracks in competitor's list
    int count1 = 0;
    int count2 = 0;
    result_pointer next = competitor1->result_list_head;
    while (next != NULL) {
        count1++;
        competitor1val += next->minutes * 600;
        competitor1val += next->seconds * 10;
        competitor1val += next->milliseconds;
        next = next->next;
    }
    next = competitor2->result_list_head;
    while (next != NULL) {
        count2++;
        competitor2val += next->minutes * 600;
        competitor2val += next->seconds * 10;
        competitor2val += next->milliseconds;
        next = next->next;
    }
    // if one of the competitors participated in more tracks than the other, they are considered better
    if (count1 > count2) return -1;
    if (count1 < count2) return 1;
    if (competitor1val > competitor2val) return 1;
    if (competitor2val > competitor1val) return -1;
    return 0;
}

/**
 * Creates and inserts new result to competitor's list  of results
 * IF none of the results is 00:00.0
 * @param competitor reference to the competitor
 * @return 0 if success, 1 if problem was encountered
 */
int addTotalResult(competitor_pointer *competitor) {
    competitor_pointer comp = *competitor;
    result_pointer next = comp->result_list_head;
    int accM, accS, accMs = 0;
    while (next != NULL) {
        if (next->minutes == 0 && next->seconds == 0 && next->milliseconds == 0) {
            return 0;
        }
        accMs += next->minutes * 600;
        accMs += next->seconds * 10;
        accMs += next->milliseconds;
        next = next->next;
    }
    accM = accMs / 600;
    accMs %= 600;
    accS = accMs / 10;
    accMs %= 10;
    next = createNewResult(comp->competitor_number, accM, accS, accMs);
    if (next == NULL) return -1;
    addResultToCompetitor(&comp, next);
    return 0;
}

/**
 * Gives competitors every result they achieved if they are not disqualified
 * @param head competitors list's head reference
 * @param track_list_head tracks list's head reference
 * @return -1 if problem was encountered, number of disqualified otherwise
 */
int giveCompetitorTheResults(competitor_pointer *head, track_pointer *track_list_head) {
    competitor_pointer next_c = *head;
    track_pointer next_t;
    result_pointer *next_r;
    int count;
    int disqualified = 0;
    int is_current_disqualified = 0;
    while (next_c != NULL) {
        next_t = *track_list_head;
        while (next_t != NULL) {
            next_r = &(next_t->result_list_head);
            result_pointer temp = *next_r;
            count = 0;
            while (temp != NULL) {
                if (temp->competitor_num == next_c->competitor_number && count == 0) {
                    count++;
                    result_pointer p = malloc(sizeof(result));
                    *p = *temp;
                    addResultToCompetitor(&next_c, p);
                } else if (temp->competitor_num == next_c->competitor_number && count > 0) {    //if competitor participated more than once on
                    clearListOfResults(&(next_c->result_list_head));                    //one track, their list is deleted
                    is_current_disqualified++;                                                  //and they are counted as disqualified
                }
                temp = temp->next;
            }
            if (count == 0) {                   //if not participated
                //insert an empty list
                temp = getEmptyResult(next_c->competitor_number);
                if (temp == NULL) {
                    return -1;
                }
                addResultToCompetitor(&next_c, temp);
            }
            next_t = next_t->next;
        }
        if (is_current_disqualified != 0) disqualified++;
        else if (addTotalResult(&next_c) == -1) return -1;
        next_c = next_c->next;
        is_current_disqualified = 0;
    }
    return disqualified;
}

