#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // tolower()

#include "exit_codes.h"
#include "option_handler.h"
#include "signal_handler.h"
#include "file_io.h"
#include "source_text.h"

exit_code_t initialize_repo(const char *path);

exit_code_t create_directories(const char *path);

exit_code_t create_gitignore(const char *path);

exit_code_t create_makefile(const char *path);

exit_code_t create_exit_codes(const char *path);

exit_code_t create_main(const char *path);

#endif