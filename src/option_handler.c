#include "option_handler.h"

void usage(char *program_name, int option)
{
    if (NULL == program_name)
    {
        fprintf(stderr, "NULL Pointer detected\n");
        goto END;
    }
    if (1 == option)
    {
        printf("\n\033[1mSUMMARY\033[m\n");
        printf("    %s - Project file generator for C and Python\n", program_name);
        printf("\n\033[1mDESCRIPTION\033[m\n");
        printf("    %s is a tool which automatically generates default project\n", program_name);
        printf("    directories and files for C or Python projects at a\n");
        printf("    user-specified project path.\n");
        printf("\n    -Files generated for C projects loosely follow the BARR-C standard\n");
        printf("    -Files generated for Python projects are PEP8 compliant.\n");
        printf("\n    For more information on files and file structure see the %s(1)\n", program_name);
        printf("    manpage (\"man %s\").\n", program_name);
        printf("\n\033[1mUSAGE\033[m\n");
        printf("    %s [options] <project_path>\n", program_name);
        printf("\n\033[1mOPTIONS\033[m\n");
        printf("    \033[1m-c\033[m     generate a C project file structure\n");
        printf("    \033[1m-p\033[m     generate a Python project file structure\n");
        printf("    \033[1m-l\033[m     specify a save location for source data\n");
        printf("    \033[1m-n\033[m     specify a program name(s) for your project\n");
        printf("    \033[1m-t\033[m     generate a template directory\n");
        printf("    \033[1m-a\033[m     generate advanced file structure (getopt, signal handler)\n");
        printf("\n    For a full listing of options, use %s --help.\n", program_name);
        printf("\n\033[1mEXAMPLES\033[m\n");
        printf("    Example 1 (C):\n");
        printf("        $ ./%s -c /home/user/project/\n", program_name);
        printf("\n    Example 2 (Python):\n");
        printf("        $ ./%s -p /home/user/project/\n", program_name);
    }
END:
    return;
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
    char program_name[] = "pk";

    while ((option = getopt(argc, argv, "cp:")) != -1)
    {
        switch (option)
        {
            case 'c':

                // Check if the c_flag was previously turned on
                if (true == options->c_flag)
                {
                    usage(program_name, 1);
                    exit_code = E_INVALID_INPUT;
                    print_exit_message(exit_code);
                    goto END;
                }

                options->c_flag = true;      
                break;
            
            case 'p':

            // Check if the p_flag was previously turned on
            if (true == options->p_flag)
            {
                usage(program_name, 1);
                exit_code = E_INVALID_INPUT;
                print_exit_message(exit_code);
                goto END;
            }

                options->p_flag = true;      
                break;

            case '?':
            default:
                fprintf(stderr, "\nOption '-%c' not supported\n", optopt);
                usage(program_name, 1);
                exit_code = E_INVALID_INPUT;
                goto END;
        }
    }

    // Set the directory path only if it exists
    char *directory;
    if (optind <= argc)
    {
        directory = argv[optind-1];

        // Check if the directory exists
        exit_code = directory_exists(directory);
        if (exit_code != E_DIRECTORY_EXISTS)
        {
            print_exit_message(exit_code);
            goto END;
        }

        // Directory is valid so set the directory path
        options->repo_path = directory;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}
