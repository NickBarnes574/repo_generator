#include "user_input.h"

exit_code_t get_input_yes_no(FILE *file_ptr, char *message)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char abort_msg[] = "\nCtrl + C detected.\nAborting...\n";

    printf("%s", message);

    char *input = calloc(1, sizeof(char *));

    while ((strcmp("y", input) != 0) || (strcmp("yes", input) != 0))
    {
        input = read_line(file_ptr, input);

        // Check for SIGINT (Ctrl + C)
        if (true == abort_program)
        {
            write(2, abort_msg, strlen(abort_msg));
            goto END;
        }

        for (size_t idx = 0; idx < strlen(input); idx++)
        {
            input[idx] = tolower(input[idx]);
        }

        if ((strcmp("y", input) == 0) || (strcmp("yes", input) == 0))
        {
            exit_code = E_YES;
            goto END;
        }

        else if ((strcmp("n", input) == 0) || (strcmp("no", input) == 0))
        {
            printf("exiting...\n");
            exit_code = E_NO;
            goto END;
        }
        else
        {
            printf("Please enter [Y] to continue or [N] to exit\n");
        }
    }

END:
    free(input);
    return exit_code;
}