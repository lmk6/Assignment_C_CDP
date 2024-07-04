//
// Created by 48505 on 08/01/2022.
//
#include "competitors_linked_list.h"
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>
#include <malloc.h>
#include "tracks_linked_list.h"
#include <stdbool.h>
#ifndef ASSIGNMENT_C_CDP_FILE_READER_H
#define ASSIGNMENT_C_CDP_FILE_READER_H
//Functions returning flags
bool isLoaded();
bool is_track_loaded();
bool isUserSure();

//returns
void loadTheCompetitorsData();
void loadTracksData();
void releaseMemory();
void programExits();

//Returns local static values
char *returnEventDate();
char *returnEventTitle();

//Functions returning head references of tracks and competitors linked lists
competitor_pointer *return_head_to_comp_list();
track_pointer *return_head_to_track_list();

//negates value of flag
void switchTrackLoaded();
#endif //ASSIGNMENT_C_CDP_FILE_READER_H
