#ifndef MESSAGES_H
#define MESSAGES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "src_paths.h"

const char *msg_notice();

const char *msg_check_save_dir();

const char *msg_init_save_dir();

const char *msg_init_repo(char **src_paths);

const char *msg_init_save_data(char **src_paths);

#endif