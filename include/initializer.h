#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // tolower()

#include "exit_codes.h"
#include "option_handler.h"
#include "signal_handler.h"
#include "file_io.h"
#include "printer.h"
#include "user_input.h"
#include "source_text.h"
#include "src_paths.h"
#include "dest_paths.h"

exit_code_t initialize_repo(options_t *options, char **src_paths, char **dest_paths);

exit_code_t initialize_source_data(options_t *options, char **src_paths);

exit_code_t initialize_destination_data(options_t *options, char **dest_paths);

exit_code_t initialize_directory(char *path, bool disp_result);

exit_code_t init_c_src_directories(char **src_paths);

exit_code_t initialize_file(char *path, const char *contents, bool disp_result);

exit_code_t init_c_src_files(char **src_paths);

exit_code_t init_c_dest_directories(char **dest_paths);

exit_code_t init_c_dest_files(char **dest_paths);






exit_code_t create_directories(options_t *options);

exit_code_t create_gitignore(options_t *options);

exit_code_t create_makefile(options_t *options);

exit_code_t create_exit_codes(options_t *options);

exit_code_t create_main(options_t *options);

#endif