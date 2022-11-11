#ifndef INITIALIZER_H
#define INITIALIZER_H

#include <stdio.h>
#include <stdlib.h>

#include "exit_codes.h"
#include "file_io.h"

exit_code_t create_directories();

exit_code_t create_gitignore();

exit_code_t create_makefile();

#endif