#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // tolower()

#include "exit_codes.h"
#include "option_handler.h"
#include "signal_handler.h"
#include "file_io.h"
#include "user_input.h"
#include "source_text.h"

typedef struct path_list path_list_t;

exit_code_t initialize_repo(options_t *options);

exit_code_t initialize_save_data(options_t *options, path_list_t *path_list);

exit_code_t create_directories(options_t *options);

exit_code_t create_gitignore(options_t *options);

exit_code_t create_makefile(options_t *options);

exit_code_t create_exit_codes(options_t *options);

exit_code_t create_main(options_t *options);

#endif