#include "option_handler.h"

void usage(char *program_name, int option)
{
    if (NULL == program_name)
    {
        fprintf(stderr, "NULL Pointer detected\n");
    }
    if (1 == option)
    {
        printf(USAGE_FMT_DEFAULT, program_name);
    }
}

exit_code_t free_options(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }
    free(options);
    options = NULL;

END:
    return exit_code;
}

exit_code_t process_options(int argc, char **argv, options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if ((NULL == argv) || (NULL == *argv) || (NULL == options))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    int option = 0;                 // Option used for getopt
    char *err;                      // Holds anything left over from a conversion
    char program_name[] = "initialize";

    while ((option = getopt(argc, argv, "c:")) != -1)
    {
        switch (option)
        {
            case 'c':

                // Check if the c_flag was previously turned on
                if (true == options->c_flag)
                {
                    usage(program_name, 1);
                    exit_code = E_INVALID_INPUT;
                    goto END;
                }

                options->c_flag = true;      
                break;

            case '?':
            default:
                fprintf(stderr, "Option '-%c' not supported\n", optopt);
                usage(program_name, 1);
                exit_code = E_INVALID_INPUT;
                goto END;
        }
    }

    // Set the directory path only if it exists and is empty
    const char *directory;
    if (optind < argc)
    {
        directory = argv[optind];

        // Check if the directory exists
        exit_code = directory_exists(directory);
        if (exit_code != E_DIRECTORY_EXISTS)
        {
            goto END;
        }

        // Check if the directory is empty
        exit_code = directory_empty(directory);
        if (exit_code != E_DIRECTORY_EMPTY)
        {
            goto END;
        }

        // Directory is valid so set the directory path
        options->repo_path = directory;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}
