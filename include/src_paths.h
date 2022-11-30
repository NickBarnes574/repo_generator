#ifndef SRC_PATHS_H
#define SRC_PATHS_H

#include <stdio.h>
#include <stdlib.h>

#include "file_io.h"

// ENUM for source paths
typedef enum src_codes
{
    DIR_REPO,
        DIR_SAVE_DATA,

        /******************
         C directory
         ******************/
        DIR_C,
            FILE_DEF_MAKEFILE, // default Makefile
            FILE_GITIGNORE, // .gitignore

            /******************
             src directory
             ******************/
            DIR_SRC,
                FILE_MAIN_C,
                FILE_EXIT_CODES_C,
            
            /******************
             include directory
             ******************/
            DIR_INCLUDE,
                FILE_MAIN_H,
                FILE_EXIT_CODES_H,
            
            /******************
             docs directory
             ******************/
            DIR_DOCS,

            /******************
             test directory
             ******************/
            DIR_TEST,
                FILE_TESTS,
                FILE_TEST_ALL,
            
            /******************
             template directory
             ******************/
            DIR_TEMPLATES,

                // makefile templates
                DIR_MAKEFILES,
                    FILE_MAKEFILE_SINGLE,
                    FILE_MAKEFILE_MULTI,
                    FILE_MAKEFILE_LIBRARY,

                // signal handler templates
                DIR_SIGNAL_HANDLER,
                    FILE_SIGNAL_HANDLER_C,
                    FILE_SIGNAL_HANDLER_H,

    NUMBER_OF_CODES,
    
} src_codes_t;

char **generate_src_paths();
void free_src_paths(char **src_paths);
void destroy_src_paths(char **src_paths);

#endif