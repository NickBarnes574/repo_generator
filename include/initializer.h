#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "file_io.h"
#include "source_text.h"

exit_code_t create_directories();

exit_code_t create_gitignore();

exit_code_t create_makefile();

exit_code_t create_exit_codes();

exit_code_t create_main();

#endif