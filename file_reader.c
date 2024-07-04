//
// Created by 48505 on 08/01/2022.
//
#include "file_reader.h"
competitor_pointer head_to_comp_list;
track_pointer head_to_track_list;
//#define DEBUG
#define BASE_DIR "Drone_Race_Data"
//global static variables
static char event_title[100];
static char event_date[10];
//local variable
char eventFolder[100];

//flags
bool loaded;
bool track_loaded;

char *returnEventDate() {
    return event_date;
}

char *returnEventTitle() {
    return event_title;
}

/**
 * @return head reference to competitors list
 */
competitor_pointer *return_head_to_comp_list() {
    return &head_to_comp_list;
}

/**
 * @return head reference to tracks list
 */
track_pointer *return_head_to_track_list() {
    return &head_to_track_list;
}

/**
 * Function asking user if he is sure of his decision
 * @return true if he is sure, false if else
 */
bool isUserSure() {
    char choice;
    while (true) {
        printf("Are you sure? [Y/N] ");
        getchar();
        fflush(stdout);
        scanf("%c", &choice);
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
 * Displays directory's contents - directories or files inside
 * @param directory opened directory
 * @param type can be either 4 or 8
 */
void displayDirectoryContent(DIR *directory, int type) {    //type = 8 is for files, type = 4 is for directories
    if (type != 4 && type != 8) {    //My design does not support other types
        printf("Type of entity unsupported by this program");
        return;
    }
    struct dirent *entity;
    entity = readdir(directory);
    int i = 0;
    while (entity != NULL) {
        if (entity->d_type == type &&
            //making sure only names of the files are visible
            strcmp(entity->d_name, ".") != 0 &&
            strcmp(entity->d_name, "..") != 0)
            printf("%d. %s\n", ++i, entity->d_name);
        entity = readdir(directory);
    }
    closedir(directory);
    free(entity);
}


/**
 * Function that asks user for name of the file
 * it traverses from base directory to sub directory if BASE_DIR exists,
 * if not, it will ask user to provide a full pathname
 * @return pathname
 */
char *getFilename() {
    DIR *directory = opendir(BASE_DIR);
    char competitor_filename[250];
    memset(competitor_filename, 0, sizeof competitor_filename);
    if (directory == NULL) {
        printf("Program did not detect '%s' directory\n", BASE_DIR);
        do {
            closedir(directory);
            printf("Please enter the name of directory for competitor file: ");
            fflush(stdout);
            scanf("%200s", competitor_filename);
            printf("\n");
            directory = opendir(competitor_filename);
            if(strcmp(competitor_filename, "exit") == 0) return "";
            if(directory == NULL) printf("DIRECTORY NOT FOUND! You can enter 'exit'\n");
        } while (directory == NULL);
        strcat(eventFolder, competitor_filename);
        char filename[50];
        strcat(competitor_filename, "\\");
        printf("Directory accessed! \n");
        do {
            printf("Please enter filename or type 'exit' to return to the menu: ");
            fflush(stdout);
            scanf("%s", filename);
            strcat(competitor_filename, filename);
            printf("\n");
            if (strcmp(competitor_filename, "exit") == 0) return "exit-to-menu";
        } while (access(competitor_filename, F_OK) != 0);
        if (!isUserSure()) return "exit-to-menu";
    } else {
        strcat(competitor_filename, BASE_DIR);
        char f_name[50];
        memset(f_name, 0, sizeof f_name);
        printf("Program detected '%s' directory which\n"
               "contains the following files:\n", BASE_DIR);
        displayDirectoryContent(directory, 4);
        closedir(directory);
        printf("Choose the folder (enter its name): ");
        fflush(stdout);
        scanf("%50s", f_name);
        printf("\n");
        strcat(competitor_filename, "\\");
        strcat(competitor_filename, f_name);
        directory = opendir(competitor_filename);
        while (directory == NULL) {
            memset(competitor_filename, 0, sizeof competitor_filename);
            strcat(competitor_filename, BASE_DIR);
            closedir(directory);
            printf("You entered wrong name\n"
                   "try again or type 'exit' to return to the menu: ");
            fflush(stdout);
            scanf("%50s", f_name);
            printf("\n");
            if (strcmp(f_name, "exit") == 0) return "exit-to-menu";
            strcat(competitor_filename, "\\");
            strcat(competitor_filename, f_name);
            directory = opendir(competitor_filename);
        }
        strcpy(eventFolder, competitor_filename);
        char temp[sizeof(competitor_filename)];
        memset(temp, 0, sizeof temp);
        strcat(temp, competitor_filename);
        printf("Found files:\n");
        displayDirectoryContent(directory, 8);
        printf("Enter the name of competitor file or \n"
               "type 'exit' to return to the menu: ");
        fflush(stdout);
        scanf("%50s", f_name);
        if (strcmp(f_name, "exit") == 0 || !isUserSure()) return "exit-to-menu";
        strcat(competitor_filename, "\\");
        strcat(competitor_filename, f_name);
        while (access(competitor_filename, F_OK) != 0) {
            memset(competitor_filename, 0, sizeof competitor_filename);
            strcat(competitor_filename, temp);
            printf("You entered wrong name\n"
                   "try again or type 'exit' to return to the menu: ");
            fflush(stdout);
            scanf("%50s", f_name);
            if (strcmp(f_name, "exit") == 0 || !isUserSure()) return "exit-to-menu";
            strcat(competitor_filename, "\\");
            strcat(competitor_filename, f_name);
        }
    }
    closedir(directory);
    char *f_name = malloc(strlen(competitor_filename) + 1);
    memset(f_name, 0, strlen(competitor_filename) + 1);
    strcat(f_name, competitor_filename);
    return f_name;
}

/**
 * Loads data from specified by getFilename() file
 */
void loadTheCompetitorsData() {
    head_to_comp_list = NULL;
    head_to_track_list = NULL;
    loaded = false;
    clearListOfTracks(&head_to_track_list);
    clearList(&head_to_comp_list);
    FILE *competitor_File;
    char *filename;
#ifndef DEBUG
    filename = getFilename();
#endif
#ifdef DEBUG
    filename = "Drone_Race_Data\\Event1_2020\\Competitors_20092020.txt";
    memset(eventFolder, 0, sizeof(eventFolder));
    strcpy(eventFolder, "Drone_Race_Data\\Event1_2020");
#endif
    if ((competitor_File = fopen(filename, "r")) != NULL) {
        char eventTitle[100];
        char eventDate[20];
        fscanf(competitor_File, "%[^\n]", eventTitle);
#ifdef DEBUG
        printf("Event title: %s\n", eventTitle);
#endif
        if (strcmp(eventTitle, "") == 0) {
            printf("There is something wrong with the content of this file\n"
                   "Please check the file and try again\n");
            return;
        }
        fscanf(competitor_File, "%s", eventDate);
#ifdef DEBUG
        printf("Event Date: %s\n", eventDate);
#endif
        if (eventDate[2] != '/') {
            printf("Format of the data is different from what is expected\n"
                   "Please check the file and try again\n");
            return;
        }
        strcpy(event_title, eventTitle);
        strcpy(event_date, eventDate);
        char fam_name[50];
        char name[50];
        char email[50];
        char license[50];
        int c_number;
        competitor_pointer new_competitor;
        reset_num_of_competitors();
        while (fscanf(competitor_File, "\n%[^\n]\n%[^\n]\n%[^\n]\n%d\n%[^\n]", fam_name, name, email, &c_number,
                      license) == 5) {
#ifdef DEBUG
            printf("family name: %s\nname: %s\nemail: %s\n"
                   "competitor number: %d\nflying license: %s\n\n",
                   fam_name, name, email, c_number, license);
#endif
            new_competitor = createNewCompetitor(fam_name, name, c_number);
            if (new_competitor == NULL) {
                printf("\nNO MEMORY LEFT\n");
                return;
            }
            insertAtTop(&head_to_comp_list, new_competitor);
        }
        loaded = true;
        if (head_to_comp_list != NULL) printf("\n%50s", "***FILE SUCCESSFULLY LOADED***");
        fclose(competitor_File);
    }
}

/**
 * helper function making debugging easier
 * prints tracks list's contents
 */
void printAllResults() {
    track_pointer nextT = head_to_track_list;
    result_pointer nextR;
    while (nextT != NULL) {
        nextR = nextT->result_list_head;
        printf("%s results: \n", nextT->track_name);
        while (nextR != NULL) {
            printf("%d achieved %d:%d.%d at %s\n", nextR->competitor_num, nextR->minutes, nextR->seconds,
                   nextR->milliseconds, nextT->time);
            nextR = nextR->next;
        }
        nextT = nextT->next;
    }
}

/**
 * Reads all the information from track data file
 * @param filename specified filename
 * @return 0 if success, 1 otherwise
 */
int loadTrackHelper(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File somehow could not be accessed!\n");
        return 1;
    }
    char *trackName = malloc(50);
    memset(trackName, 0, 50);
    char *date = malloc(11);
    memset(date, 0, 11);
    char *time = malloc(9);
    memset(time, 0, 9);
    int compNum, m = 0, s = 0, ms = 0;
    char buffer[50];
    memset(buffer, 0, sizeof(buffer));
    fscanf(file, "%50[^\n]", trackName);
    fscanf(file, "%10s", date);
    if (strcmp(event_date, date) != 0) {
        printf("Dates are different!\n");
        fclose(file);
        return 1;
    }
    fscanf(file, "%8s", time);
    track_pointer new_track;
    //prevents creating the same track again
    if (checkIfTrackAlreadyExists(&head_to_track_list, trackName, date) == 1) {
        new_track = createNewTrack(trackName, date, time);
        if (new_track == NULL) {
            printf("Run out of memory!\n");
            fclose(file);
            return 1;
        }
        insertAtTopOfTrackList(&head_to_track_list, new_track);
    } else new_track = getExistingTrack(&head_to_track_list, trackName, date);
    new_track = getExistingTrack(&head_to_track_list, trackName, date);
    if(new_track == NULL) new_track = createNewTrack(trackName, date, time);
    if (new_track == NULL) {
        printf("Run out of memory\n");
        fclose(file);
        return 1;
    }
    while (fscanf(file, "\n%s", buffer) == 1) {
        if (strlen(buffer) == 0) break;
        if (sscanf(buffer, "%d,%d:%d.%d", &compNum, &m, &s, &ms) == EOF) {
            printf("File's contents does not match required format");
            fclose(file);
            return 1;
        }
#ifdef DEBUG
        printf("%s: %d,%d:%d.%d\n", trackName, compNum, m, s, ms);
#endif
        if (insertNewResult(&new_track, compNum, m, s, ms) == 1) {
            printf("Run out of memory!");
            fclose(file);
            return 1;
        }

    }
    if(head_to_comp_list != NULL) track_loaded = true;
    free(trackName);
    free(date);
    free(time);
    fclose(file);
    return 0;
}

/**
 * Searches for files with name in specified format and reads
 * them one by one
 */
void loadTracksData() {
    clearListOfTracks(&head_to_track_list);
    char track_filename[150];
    char *temp = malloc(sizeof(track_filename));
    char *tempFullPath = malloc(sizeof(track_filename));
    char index[4];
    bool loop = true;
    strcpy(track_filename, eventFolder);
    strcat(track_filename, "\\");
    strcpy(temp, track_filename);

    for (int j = 1; loop; j++) {
        strcpy(track_filename, temp);
        strcat(track_filename, "Track");
        sprintf(index, "%d", j);
        strcat(track_filename, index);
        strcat(track_filename, "_");
        strcpy(tempFullPath, track_filename);
        for (int i = 1; true; i++) {
            memset(track_filename, 0, sizeof(track_filename));
            strcpy(track_filename, tempFullPath);
            sprintf(index, "%d", i);
            strcat(track_filename, index);
            memset(index, 0, sizeof(index));
            strcat(track_filename, ".txt");
            if (access(track_filename, F_OK) == 0) {
                if (loadTrackHelper(track_filename) == 1) {
                    return;
                }
            } else if (j == 1 && i == 1) {
                printf("Program did not detect any tracks record!\n");
                loop = false;
                break;
            } else if (i == 1) {
                loop = false;
                break;
            } else {
                break;
            }
        }
    }
#ifdef DEBUG
    printAllResults();
#endif
    free(temp);
    free(tempFullPath);
    if(head_to_track_list != NULL) printf("%34s", "**Successfully loaded!**\n");
}

/**
 * @return 'is loaded' flag
 */
bool isLoaded() {
    return loaded;
}

/**
 * @return 'is track loaded' flag
 */
bool is_track_loaded() {
    return track_loaded;
}

/**
 * negates 'is track loaded' flag
 */
void switchTrackLoaded() {
    track_loaded = !track_loaded;
}