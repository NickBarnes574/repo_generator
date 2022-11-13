#include "printer.h"

void print_dots_str(FILE *file_ptr, char *title, char *data)
{
    static const char padder[] = "...........................................................................";

    size_t title_len = strlen(title);
    size_t pad_amount = sizeof(padder) - 1 - title_len;

    fprintf(file_ptr, "%s", title);

    if (pad_amount > 0)
    {
        fprintf(file_ptr, "%s", (padder + title_len)); // chop the string
    }

    fprintf(file_ptr, "%s", data);
}