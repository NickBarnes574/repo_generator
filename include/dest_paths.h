#ifndef DEST_PATHS_H
#define DEST_PATHS_H

#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

// ENUM for destination paths
typedef enum dest_codes
{
    DEST_DIR_REPO,
        /*1. */ DEST_FILE_DEF_MAKEFILE, // default Makefile
        /*2. */ DEST_FILE_GITIGNORE, // .gitignore

        /******************
         src directory
            ******************/
        DEST_DIR_SRC,
            /*1. */ DEST_FILE_MAIN_C,
            /*2. */ DEST_FILE_EXIT_CODES_C,
        
        /******************
         include directory
            ******************/
        DEST_DIR_INCLUDE,
            /*1. */ DEST_FILE_MAIN_H,
            /*2. */ DEST_FILE_EXIT_CODES_H,
        
        /******************
         docs directory
            ******************/
        DEST_DIR_DOCS,

        /******************
         test directory
            ******************/
        DEST_DIR_TEST,
            /*1. */ DEST_FILE_TESTS,
            /*2. */ DEST_FILE_TEST_ALL,
        
        /******************
         template directory
            ******************/
        DEST_DIR_TEMPLATES,

            // makefile templates
            DEST_DIR_MAKEFILES,
                /*1. */ DEST_FILE_MAKEFILE_SINGLE,
                /*2. */ DEST_FILE_MAKEFILE_MULTI,
                /*3. */ DEST_FILE_MAKEFILE_LIBRARY,

            // signal handler templates
            DEST_DIR_SIGNAL_HANDLER,
                /*1. */ DEST_FILE_SIGNAL_HANDLER_C,
                /*2. */ DEST_FILE_SIGNAL_HANDLER_H,

    DEST_NUMBER_OF_CODES,
    
} dest_codes_t;

char **generate_dest_paths(const char *path);
void free_dest_paths(char **dest_paths);
void destroy_dest_paths(char **dest_paths);

#endif