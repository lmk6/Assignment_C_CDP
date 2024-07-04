//
// Created by 48505 on 09/01/2022.
//
#include <stdbool.h>
#include "tracks_linked_list.h"
#include "trackResults_linked_list.h"
#include "file_reader.h"
#include "data_format.h"
#ifndef ASSIGNMENT_C_CDP_COMPETITIONDAY_H
#define ASSIGNMENT_C_CDP_COMPETITIONDAY_H
//Returns flag
bool is_track_provided();

//Menu features
void enterManually();
void getResultTable();

//Gets head references from file_reader
void enteredByLoading();
#endif //ASSIGNMENT_C_CDP_COMPETITIONDAY_H
