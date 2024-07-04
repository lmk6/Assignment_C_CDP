//
// Created by lmk6 on 07/01/2022.
//
#include "trackResults_linked_list.h"
#ifndef ASSIGNMENT_C_DATA_FORMAT_H
#define ASSIGNMENT_C_DATA_FORMAT_H
//returns data in different formats
char *dateFormat(char *date);
int dateValidator(int day, int month, int year);
int timeValidator(int minute, int second, int millisecond);
char *getTimeFormat(result_pointer result);
char *formattedTime(int m, int s, int ms);
#endif //ASSIGNMENT_C_DATA_FORMAT_H
