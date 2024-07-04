# Competition Day Program

The program is written in C11 using the CLion IDE.
To build program you simply have to build the project in the IDE.

## User notes:

Drone_Race_Data directory and its contents are located in cmake-build-debug.

cmake-build-debug is the default CMake runtime directory.

End of user notes.

## Files:

- main.c <- main function
- competitionDay.c <- provides competition results table and allows to enter results manually
- competitionDay.h
- competitors_linked_list.c <- provides linked list data structure to store competitors
- competitors_linked_list.h
- data_format.c <- provides functions to format data
- data_format.h
- file_reader.c <- reads competitors data from file, allows to read tracks data from file
- file_reader.h
- trackResults_linked_list.c <- provides linked list data structure to store results
- trackResults_linked_list.h
- tracks_linked_list.c <- provides linked list data structure to store tracks
- tracks_linked_list.h

## libraries:
- stdlib.h
- malloc.h
- string.h
- ctype.h
- stdio.h
- dirent.h
- unistd.h
- stdbool.h