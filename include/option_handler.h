#ifndef OPTION_HANDLER_H
#define OPTION_HANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>     // getopt
#include <stdbool.h>    // bool
#include <stdint.h>     // unint32_t

#include "exit_codes.h"
#include "file_io.h"

#define USAGE_FMT_DEFAULT "%s [-c repo_path]\n"

typedef struct 
{
    bool c_flag;    // Used to set the truth value for the C flag
    char *repo_path;
} options_t;

/**
 * @brief Displays the usage of the program to the user.
 * 
 * @param program_name the name of the program.
 * @param option the option that was passed in.
 */
void usage(char *program_name, int option);

/**
 * @brief Frees memory for the options_t struct.
 * 
 * @param options the options_t struct to be passed in.
 * @return exit_code_t SUCCESS = 0 (E_SUCCESS), anything else is considered a failure.
 */
exit_code_t free_options(options_t *options);

/**
 * @brief Processes and parses command line arguments using getopt().
 * 
 * @param argc The number of arguments on the command line.
 * @param argv The arguments to be passed in.
 * @param options The options_t struct to be passed in.
 * @return exit_code_t SUCCESS = 0 (E_SUCCESS), anything else is considered a failure.
 */
exit_code_t process_options(int argc, char **argv, options_t *options);

#endif
