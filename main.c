//
// Created by lmk6 on 08/01/2022.
//
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include "file_reader.h"
#include "competitionDay.h"

/**
 * function to print menu
 */
void printMenu() {
    printf("\n\n%*s\n", 20, "MAIN MENU");
    printf("%30s\n", "O - Open the competitor file");
    printf("%40s\n", "M - Manually enter competition results");
    printf("%37s\n", "R - Read all lap time results files");
    printf("%43s\n", "P - Produce the competition results table");
    printf("%10s\n", "X - Exit");
}

/**
 * function to check if any file was loaded
 * @return
 */
bool checkIfLoaded() {
    if (!isLoaded()) {
        printf("No file is opened!\n");
    }
    return isLoaded();
}

/**
 * prints an appropriate message if no race results were provided
 * @return true if tracks are loaded or manually provide, false otherwise
 */
bool checkIfTracksProvided() {
    if (!is_track_provided() && !is_track_loaded()) {
        printf("No race results provided!\n");
    }
    return is_track_loaded() || is_track_provided();
}

/**
 * function allowing the user to
 * select menu options
 */
void menuSelection() {
    char selection;
    bool loop = true;
    while (loop) {
        printMenu();
        printf("Enter your choice: ");
        fflush(stdout);     // for some reason there was nothing displaying in my terminal
        // this solution apparently fixes it
        scanf("%c", &selection);
        switch (tolower(selection)) {
            case 'o':
                loadTheCompetitorsData();
                break;
            case 'm':
                if (checkIfLoaded()) {
                    if (is_track_loaded() || is_track_loaded()) {
                        printf("WARNING: loaded data will be lost!");
                        if (isUserSure()) enterManually();
                    } else enterManually();
                }
                break;
            case 'r':
                if (checkIfLoaded()) {
                    if (is_track_loaded() || is_track_provided()) {
                        printf("WARNING: previous track results will be lost!\n");
                        if (isUserSure()) {
                            loadTracksData();
                            enteredByLoading();
                        }
                    } else {
                        loadTracksData();
                        enteredByLoading();
                    }
                }
                break;
            case 'p':
                if (checkIfTracksProvided()) getResultTable();
                break;
            case 'x':
                if (isUserSure()) {
                    programExits();
                    printf("%30s", "--Goodbye--");
                    loop = false;
                }
                break;
            default:
                printf("%50s", "Incorrect input, please try again\n");
                fflush((stdout));
        }
        getchar();
    }
}

/**
 * main function
 */
int main() {
    menuSelection();
}