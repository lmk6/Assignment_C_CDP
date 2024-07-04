//
// Created by 48505 on 08/01/2022.
//
#include "trackResults_linked_list.h"
#ifndef ASSIGNMENT_C_CDP_TRACKS_LINKED_LIST_H
#define ASSIGNMENT_C_CDP_TRACKS_LINKED_LIST_H

//track struct and its pointer
typedef struct track_tag *track_pointer;
typedef struct track_tag {
    char track_name[20];
    char date[10];
    char *time;
    result_pointer result_list_head;
    track_pointer next;
} track;

//track constructor
track_pointer createNewTrack(char *tName, char *date, char *time);

//list manipulating/traversing functions
void insertAtTopOfTrackList(track_pointer *ptr_to_head, track_pointer new_ptr);
void clearListOfTracks(track_pointer *head_ref);
int insertNewResult(track_pointer *trackPointer, int compNum,
                     int minutes, int seconds, int milliseconds);
int checkIfTrackAlreadyExists(track_pointer *head, char *name, char *date);
track_pointer getExistingTrack(track_pointer *head, char *name, char *date);
int howManyTracks(track_pointer *ptr_to_track_lists_head);

//Alternative constructor
result_pointer getEmptyResult(int compNum);
#endif //ASSIGNMENT_C_CDP_TRACKS_LINKED_LIST_H
