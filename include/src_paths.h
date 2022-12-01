#ifndef SRC_PATHS_H
#define SRC_PATHS_H

#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

// ENUM for source paths
typedef enum src_codes
{
    SRC_DIR_REPO,
        SRC_DIR_SAVE_DATA,

        /******************
         C directory
         ******************/
        SRC_DIR_C,
            /*1. */ SRC_FILE_DEF_MAKEFILE, // default Makefile
            /*2. */ SRC_FILE_GITIGNORE, // .gitignore

            /******************
             src directory
             ******************/
            SRC_DIR_SRC,
                /*1. */ SRC_FILE_MAIN_C,
                /*2. */ SRC_FILE_EXIT_CODES_C,
            
            /******************
             include directory
             ******************/
            SRC_DIR_INCLUDE,
                /*1. */ SRC_FILE_MAIN_H,
                /*2. */ SRC_FILE_EXIT_CODES_H,
            
            /******************
             docs directory
             ******************/
            SRC_DIR_DOCS,

            /******************
             test directory
             ******************/
            SRC_DIR_TEST,
                /*1. */ SRC_FILE_TESTS,
                /*2. */ SRC_FILE_TEST_ALL,
            
            /******************
             template directory
             ******************/
            SRC_DIR_TEMPLATES,

                // makefile templates
                SRC_DIR_MAKEFILES,
                    /*1. */ SRC_FILE_MAKEFILE_SINGLE,
                    /*2. */ SRC_FILE_MAKEFILE_MULTI,
                    /*3. */ SRC_FILE_MAKEFILE_LIBRARY,

                // signal handler templates
                SRC_DIR_SIGNAL_HANDLER,
                    /*1. */ SRC_FILE_SIGNAL_HANDLER_C,
                    /*2. */ SRC_FILE_SIGNAL_HANDLER_H,

    SRC_NUMBER_OF_CODES,
    
} src_codes_t;

char **generate_src_paths();
void free_src_paths(char **src_paths);
void destroy_src_paths(char **src_paths);

#endif