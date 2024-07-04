//
// Created by 48505 on 09/01/2022.
//

#include <stdlib.h>
#include "competitionDay.h"

//Global variables
bool track_provided;
competitor_pointer comp_list_head;
track_pointer track_list_head;

/**
 * Return 'are track results provided' flag
 * @return true if track results were provided, false otherwise
 */
bool is_track_provided() {
    return track_provided;
}

/**
 * Asks user if they want to add more tracks
 * @return true if yes, false otherwise
 */
bool moreTracks() {
    char choice;
    while (true) {
        printf("Do you wish to add another track? [Y/N] ");
        getchar();
        fflush(stdout);
        int status = scanf("%c", &choice);
        if (status != 1) {
            printf("Wrong input detected, returning no\n");
            return false;
        }
        switch (tolower(choice)) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                printf("Wrong input, try again\n");
        }
    }
}

/**
 * Asks user to provide results for the track
 * @param trackPointer selected track
 * @return 0 if entered successfully, 1 otherwise
 */
int enterNewTrackResults(track_pointer *trackPointer) {
    track_pointer the_track = *trackPointer;
    int competitorNumber;
    char *time = malloc(7);
    memset(time, 0, 7);
    int min, sec, ms;
    printf("Enter competitor's number: ");
    int status = scanf("%d", &competitorNumber);
    if (status != 1) {
        printf("Wrong input type!\n");
        fflush(stdout);
        return 1;
    }
    printf("\n");
    printf("Enter time (in mm:ss.s - precision to 1/10 of a second): ");
    scanf("%7s", time);
    printf("\n");
    status = sscanf(time, "%d:%d.%d", &min, &sec, &ms);
    if (status != 3 || timeValidator(min, sec, ms)) {
        printf("Wrong time format!\n");
        return 1;
    }
    if (insertNewResult(&the_track, competitorNumber, min, sec, ms) == 1) {
        printf("Run out of memory!\n");
        return 1;
    }
    return 0;
}

/**
 * Asks user if they want to add another track result
 * @return true if yes, not otherwise
 */
bool userWantsMore() {
    char choice;
    while (true) {
        printf("Another Result? [Y/N] ");
        getchar();
        fflush(stdout);
        int status = scanf("%c", &choice);
        if (status != 1) {
            printf("Wrong input detected, returning no\n");
            return false;
        }
        switch (tolower(choice)) {
            case 'y':
                return true;
            case 'n':
                return false;
            default:
                printf("Wrong input, try again\n");
        }
    }
}

/**
 * Produces the competition results table
 * Makes big use of giveCompetitorTheResults() function
 */
void getResultTable() {
    int numOfDisqualified = giveCompetitorTheResults(&comp_list_head, &track_list_head);
    int numOfQualified = getNum_of_competitors() - numOfDisqualified;
    if (numOfQualified <= 0) {
        printf("Something went terribly wrong\n");
        return;
    }
    competitor qualifiedArr[numOfQualified];
    competitor_pointer next = comp_list_head;
    competitor disqualifiedArr[numOfDisqualified];
    int i = 0, j = 0;
    while (next != NULL) {
        if (next->result_list_head != NULL) qualifiedArr[i++] = *next;
        if (next->result_list_head == NULL) disqualifiedArr[j++] = *next;
        next = next->next;
    }
    int num_of_tracks = howManyTracks(&track_list_head) + 1;

    qsort(qualifiedArr, i, sizeof(competitor), compareTotalTimes);
    char *fullname = malloc(100);
    memset(fullname, 0, 100);

    int numOfTracks = 0;
    char *results[num_of_tracks];
    int unfinished = 0;
    result_pointer next_res;
    track_pointer next_track = track_list_head;
    int numOfChars;
    printf("Competition: %s Date: %s\n", returnEventTitle(), dateFormat(returnEventDate()));
    printf("%-31s %-18s", "NAME", "Competitor");
    numOfChars = 31 + 18;
    while (next_track != NULL) {
        printf("%-12s", next_track->track_name);
        numOfChars += 12;
        next_track = next_track->next;
    }
    printf("%s", "Total");
    numOfChars += 6;
    printf("\n");
    for (int x = 0; x <= numOfChars; x++) printf("=");
    printf("\n");
    for (int index = 0; index < numOfQualified; index++) {
        strcpy(fullname, qualifiedArr[index].name);
        strcat(fullname, " ");
        strcat(fullname, qualifiedArr[index].family_name);
        printf("%-40s %-8d ", fullname, qualifiedArr[index].competitor_number);
        next_res = qualifiedArr[index].result_list_head;
        while (numOfTracks < num_of_tracks) {
            if (next_res != NULL) {
                results[numOfTracks++] = getTimeFormat(next_res);
                next_res = next_res->next;
            } else {
                results[numOfTracks++] = "";
                unfinished++;
            }
        }
        //not likely to become a negative value but for the sake of safety...
        if ((num_of_tracks - 1 - unfinished) > 0)
            for (int m = num_of_tracks - 1 - unfinished; m >= 0; m--)   //
                printf("%-12s", results[m]);

        numOfTracks = 0;
        unfinished = 0;
        memset(fullname, 0, 100);
        printf("\n");
    }
    clearAllResults(&comp_list_head);
}

/**
 * Takes head references to both track and competitor linked lists
 */
void enteredByLoading() {
    comp_list_head = *return_head_to_comp_list();
    track_list_head = *return_head_to_track_list();
}

/**
 * Allows user to enter the results manually
 */
void enterManually() {
    comp_list_head = *return_head_to_comp_list();
    track_list_head = NULL;
    track_pointer new_track;
    char *trackName = malloc(10);
    memset(trackName, 0, 10);
    char index[4];
    bool loop = true;
    for (int i = 1; loop; i++) {
        strcpy(trackName, "Track");
        sprintf(index, "%d", i);
        strcat(trackName, index);
        if (checkIfTrackAlreadyExists(&track_list_head, trackName, returnEventDate()) == 1) {
            new_track = createNewTrack(trackName, trackName, "00:00:00");
            if (new_track == NULL) {
                printf("Run out of memory!\n");
                return;
            }
            insertAtTopOfTrackList(&track_list_head, new_track);
        } else new_track = getExistingTrack(&track_list_head, trackName, "00:00:00");
        printf("You will now enter results for %s:\n", trackName);
        do {
            if (enterNewTrackResults(&new_track) == 1) return;
        } while (userWantsMore());
        if (!moreTracks()) loop = false;
    }
    free(trackName);
    if (track_list_head != NULL) {
        printf("%30s", "**RESULTS ENTERED**\n");
        track_provided = true;
    }
}

/**
 * negates appropriate flags and initiates lists' emptying
 */
void releaseMemory() {
    if (is_track_loaded()) {
        enteredByLoading();
        switchTrackLoaded();
    } else track_provided = !track_provided;
    clearListOfTracks(&track_list_head);
    clearList(&comp_list_head);
}

/**
 * Executes pre-exit operations
 */
void programExits() {
    releaseMemory();
}