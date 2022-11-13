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

typedef struct src_paths src_paths_t;
typedef struct dest_paths dest_paths_t;

exit_code_t initialize_repo(options_t *options);

exit_code_t initialize_save_data(options_t *options, src_paths_t *src_paths);

exit_code_t create_directories(options_t *options);

exit_code_t init_c_src_directories(src_paths_t *src_paths);

exit_code_t init_c_src_files(src_paths_t *src_paths);

exit_code_t init_c_dest_directories(dest_paths_t *dest_paths);

exit_code_t init_c_dest_files(dest_paths_t *dest_paths, src_paths_t *src_paths);

exit_code_t create_gitignore(options_t *options);

exit_code_t create_makefile(options_t *options);

exit_code_t create_exit_codes(options_t *options);

exit_code_t create_main(options_t *options);

#endif