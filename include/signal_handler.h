#ifndef SIGNAL_HANDLER_H
#define SIGNAL_HANLDER_H

#define _GNU_SOURCE
#include <signal.h>
#include <stdatomic.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>

extern volatile sig_atomic_t abort_program;

/**
 * @brief Function to setup signal handling
 *
 */
void signal_setup();

#endif
