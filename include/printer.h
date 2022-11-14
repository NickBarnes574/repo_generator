#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_dots_str(FILE *file_ptr, char *title, char *data);
void print_leader_line(FILE *file_ptr, const char *suffix, char *beginning, const char *end);

#endif