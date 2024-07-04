//
// Created by 48505 on 08/01/2022.
//

#include "tracks_linked_list.h"
#include <malloc.h>
#include <string.h>

/**
 * New Track constructor
 * @param tName track name
 * @param date date
 * @param time time
 * @return created track
 */
track_pointer createNewTrack(char *tName, char *date, char *time) {
    track_pointer new_track;
    new_track = malloc(sizeof(track));
    if (new_track == NULL) return NULL;
    strcpy(new_track->track_name, tName);
    new_track->time = malloc(strlen(time) + 1);
    new_track->time = time;
    strcpy(new_track->date, date);
    new_track->result_list_head = NULL;
    new_track->next = NULL;
    return new_track;
}

/**
 * Inserts new track to the list
 * @param ptr_to_head reference to head
 * @param new_ptr pointer to new track
 */
void insertAtTopOfTrackList(track_pointer *ptr_to_head, track_pointer new_ptr) {
    new_ptr->next = *ptr_to_head;
    *ptr_to_head = new_ptr;
}

/**
 * Function called to completely clear the list's
 * contents from memory
 * @param head_ref reference to head of the list
 */
void clearListOfTracks(track_pointer *head_ref) {
    track_pointer current = *head_ref;
    track_pointer next;
    while (current != NULL) {
        next = current->next;
        clearListOfResults(&(current->result_list_head));
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

/**
 * Inserts new result to provided track
 * @param trackPointer reference to the track
 * @param compNum competitor number
 * @param min minute
 * @param s second
 * @param ms millisecond
 * @return 1 if failed, 0 if succeeded
 */
int insertNewResult(track_pointer *trackPointer, int compNum, int min, int s, int ms) {
    track_pointer theTrack = *trackPointer;
    result_pointer new_result = createNewResult(compNum, min, s, ms);
    if(new_result == NULL) return 1;
    insertAtTopOfResultsList(&(theTrack->result_list_head), new_result);
    return 0;
}

/**
 * checks if track already exists by comparing name and date
 * @param head reference to head of the list
 * @param name track name
 * @param date
 * @return 0 if already exists, 1 otherwise
 */
int checkIfTrackAlreadyExists(track_pointer *head, char *name, char *date) {
    track_pointer next = *head;
    while (next != NULL) {
        if(strcmp(next->track_name, name) == 0 && strcmp(next->date, date) == 0)
            return 0;   //Already exists
        next = next->next;
    }
    return 1;       //does not exist
}

/**
 * Returns track if exists
 * @param head reference to head
 * @param name track name
 * @param date track date
 * @return track with the same parameters or NULL
 */
track_pointer getExistingTrack(track_pointer *head, char *name, char *date) {
    track_pointer next = *head;
    while (next != NULL) {
        if(strcmp(next->track_name, name) == 0 && strcmp(next->date, date) == 0)
            return next;   //Already exists
        next = next->next;
    }
    return NULL;       //does not exist
}

/**
 * @param head reference to the head of the list
 * @return number of tracks in the list
 */
int howManyTracks(track_pointer *head) {
    track_pointer next = *head;
    int i = 0;
    while(next != NULL) {
        i++;
        next = next->next;
    }
    return i;
}