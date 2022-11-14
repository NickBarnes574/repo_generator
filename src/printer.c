#include "printer.h"

void print_dots_str(FILE *file_ptr, char *title, char *data)
{
    const char padder[] = "...........................................................................";

    size_t title_len = strlen(title);
    size_t pad_amount = sizeof(padder) - 1 - title_len;

    fprintf(file_ptr, "%s", title);

    if (pad_amount > 0)
    {
        fprintf(file_ptr, "%s", (padder + title_len)); // chop the string
    }

    fprintf(file_ptr, "%s", data);
}

void print_leader_line(FILE *file_ptr, const char *suffix, char *beginning, const char *end)
{
    char title[256] = "";
    char data[256] = "";

    strcpy(title, (const char*)suffix);
    strcat(title, ": [");
    strcat(title, (const char*)beginning);
    strcat(title, "]");

    strcpy(data, "[");
    strcat(data, end);
    strcat(data, "]\n");

    print_dots_str(file_ptr, title, data);
}