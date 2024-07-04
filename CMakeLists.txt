cmake_minimum_required(VERSION 3.21)
project(Assignment_C_CDP)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Assignment_C_CDP
        .idea/.gitignore
        .idea/Assignment_C_CDP.iml
        .idea/modules.xml
        .idea/workspace.xml
        competitionDay.c
        competitionDay.h
        competitors_linked_list.c
        competitors_linked_list.h
        data_format.c
        data_format.h
        file_reader.c
        file_reader.h
        main.c
        trackResults_linked_list.c
        trackResults_linked_list.h
        tracks_linked_list.c
        tracks_linked_list.h)
