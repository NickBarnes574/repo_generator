#ifndef USER_INPUT_H
#define USER_INPUT_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> // tolower()

#include "exit_codes.h"
#include "option_handler.h"
#include "signal_handler.h"
#include "file_io.h"

exit_code_t get_input_yes_no(FILE *file_ptr, char *message);

#endif