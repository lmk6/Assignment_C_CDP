//
// Created by lmk6 on 07/01/2022.
//

#include "data_format.h"
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdio.h>

/**
 * Function checking if given string contains only digits
 * @param number provided string
 * @return 1 if no, 0 if yes
 */
int containsDigitsOnly(const char *number) {
    for (int i = 0; number[i] != '\0'; i++) {
        if (isdigit(number[i]) == 0) return 1;
    }
    return 0;
}

/**
 * Function checking if given date is real
 *
 * @param day day number
 * @param month month number
 * @param year year number
 * @return 1 if date is not real, 0 if date is fine
 */
int dateValidator(int day, int month, int year) {
    if (day < 1 || month < 1) {
        printf("Zeroth or negative month or day is not valid\n");
        return 1;
    }
    if (month > 12) {
        printf("There are only 12 months!\n");
        return 1;
    }
    if ((month == 2 || month == 4 || month == 6 || month == 9 ||
         month == 11) && day > 30) {
        printf("Selected month can have up to 31 days!\n");
        return 1;
    } else if (month == 2) {
        if (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0) && day > 29) {
            printf("Selected month can have up to 29 days!\n");
            return 1;
        } else if (day > 28) {
            printf("Selected month can have up to 28 days!\n");
            return 1;
        }
    } else if (day > 31) {
        printf("Selected month can have up to 30 days!\n");
        return 1;
    }
    return 0;
}

/**
 * Function returning full name of month for
 * corresponding month number
 * @param month_N month number
 * @return month in string if month number is correct,
 * NULL if not
 */
char *getMonth(int month_N) {
    if (month_N == 1) return "January";
    if (month_N == 2) return "February";
    if (month_N == 3) return "March";
    if (month_N == 4) return "April";
    if (month_N == 5) return "May";
    if (month_N == 6) return "June";
    if (month_N == 7) return "July";
    if (month_N == 8) return "August";
    if (month_N == 9) return "September";
    if (month_N == 10) return "October";
    if (month_N == 11) return "November";
    if (month_N == 12) return "December";
    else return "NULL";
}

/**
 * Function converting date from file format to nice one
 * @param date_t date in dd/mm/yyyy format
 * @return date in elegant format
 */
char *dateFormat(char *date_t) {
    char *date = malloc(sizeof(char) * 10 + 1);
    strcpy(date, date_t);
    char *day = malloc(sizeof(char) * 4 + 1);
    int d;
    int m;
    char year[4];       //chosen by design, no acceptance of year over 9999
    if (strlen(date) != 10 && date[2] == '/' && date[5] == '/') return "NULL";
    char *part = strtok(date, "/");
    for (int i = 0; i < 3; i++) {
        if (!containsDigitsOnly(part)) {
            if (i == 0) d = (int) strtol(part, (char **) NULL, 10);
            if (i == 1) m = (int) strtol(part, (char **) NULL, 10);
            if (i == 2) strcpy(year, part);
        } else return "NULL";
        part = strtok(NULL, "/");
    }
    free(part);
    free(date);
    if (dateValidator(d,
                      m,
                      (int) strtol(year, (char **) NULL, 10)) == 1)
        return "NULL";
    char fullDate[20];
    sprintf(day, "%d", d);
    memset(fullDate, 0, sizeof(fullDate));
    if (day[1] == '1') strcat(day, "st");
    else if (day[1] == '2') strcat(day, "nd");
    else if (day[1] == '3') strcat(day, "rd");
    else strcat(day, "th");
    strcat(fullDate, day);
    free(day);
    strcat(fullDate, " ");
    strcat(fullDate, getMonth(m));
    strcat(fullDate, " ");
    strcat(fullDate, year);
    char *fullDate_p = strdup(fullDate);
    return fullDate_p;
}

/**
 * Checks if time is correct
 * @param m minutes
 * @param s seconds
 * @param ms milliseconds
 * @return 1 if incorrect, 0 if correct
 */
int timeValidator(int m, int s, int ms) {
    if (m > 59 || m < 0) return 1;
    if (s > 59 || s < 0) return 1;
    if (ms > 9 || ms < 0) return 1;
    return 0;
}

/**
 * Converts result's time into nicely formatted string
 * @param result
 * @return formatted time - mm:ss.ms
 */
char *getTimeFormat(result_pointer result) {
    if(result == NULL) return formattedTime(0, 0, 0);
    else return formattedTime(result->minutes, result->seconds, result->milliseconds);
}

/**
 * Returns time in a strict format - 00:00.0
 * @param m minutes
 * @param s seconds
 * @param ms milliseconds
 * @return formatted time
 */
char *formattedTime(int m, int s, int ms) {
    char *time = malloc(8);
    memset(time, 0, 8);
    char *temp = malloc(3);
    memset(temp, 0, 3);
    sprintf(temp, "%01d", m);
    strcat(time, temp);
    memset(temp, 0, 3);
    strcat(time, ":");
    sprintf(temp, "%02d", s);
    strcat(time, temp);
    strcat(time, ".");
    memset(temp, 0, 3);
    sprintf(temp, "%01d", ms);
    strcat(time, temp);
    free(temp);
    return time;
}