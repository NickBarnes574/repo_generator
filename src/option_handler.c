#include "option_handler.h"

void usage(char *program_name)
{
    if (NULL == program_name)
    {
        fprintf(stderr, "NULL Pointer detected\n");
        goto END;
    }
    // Usage
    printf("\n\033[1mUSAGE\033[m\n");
    printf("    %s -c <project_path> [-n <program_name(s)...>]\n", program_name);

    // Options
    printf("\n\033[1mOPTIONS\033[m\n");
    printf("    \033[1m-c\033[m     generate a C project\n");
    printf("    \033[1m-n\033[m     specify a program name(s) for your project\n");
    printf("\n    For a full listing of options and detailed descriptions, use %s --help.\n", program_name);

    // Examples
    printf("\n\033[1mEXAMPLES\033[m\n");
    printf("    Example 1 (C):\n");
    printf("        $ ./%s -c /home/user/project -n encode decode\n", program_name);
    printf("\n    Example 2 (Python):\n");
    printf("        $ ./%s -p /home/user/project\n", program_name);

END:
    return;
}

void help(char *program_name)
{
    if (NULL == program_name)
    {
        fprintf(stderr, "NULL Pointer detected\n");
        goto END;
    }
    // Summary
    printf("\n\033[1mSUMMARY\033[m\n");
    printf("    %s - Project file generator for C\n", program_name);

    // Description
    printf("\n\033[1mDESCRIPTION\033[m\n");
    printf("    %s is a tool which automatically generates default project\n", program_name);
    printf("    directories and files for C or projects at a user-specified\n");
    printf("    project path.\n");
    printf("\n    -Files generated for C projects loosely follow the BARR-C standard\n");
    printf("\n    For more information on files and file structure see the %s(1)\n", program_name);
    printf("    manpage (\"man %s\").\n", program_name);

    // Usage
    printf("\n\033[1mUSAGE\033[m\n");
    printf("    %s -c <project_path> [-n <program_name(s)...>]\n", program_name);

    // Options
    printf("\n\033[1mOPTIONS\033[m\n");
    printf("    \033[1m-c\033[m     generate a C project\n");
    printf("    \033[1m-n\033[m     specify a program name(s) for your project\n");

    // Examples
    printf("\n\033[1mEXAMPLES\033[m\n");
    printf("    Example 1 (C):\n");
    printf("        $ ./%s -c /home/user/project -n encode decode\n", program_name);
    printf("\n    Example 2 (C):\n");
    printf("        $ ./%s -c /home/user/project\n", program_name);


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

    free(options->prog_names);
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

    char program_name[] = "pk";

    if (argc < 2)
    {
        exit_code = E_OUT_OF_BOUNDS;
        printf("Must have at least one option -c <project_path>\n");
        usage(program_name);
        goto END;
    }

    int option = 0;                 // Option used for getopt

    while ((option = getopt(argc, argv, "c:n:h")) != -1)
    {
        switch (option)
        {
            case 'c':

                // Check if the c_flag was previously turned on
                if (true == options->c_flag)
                {
                    usage(program_name);
                    exit_code = E_INVALID_INPUT;
                    print_exit_message(exit_code);
                    goto END;
                }

                // Check if the directory exists
                exit_code = directory_exists(optarg);
                if (exit_code != E_DIRECTORY_EXISTS)
                {
                    print_exit_message(exit_code);
                    goto END;
                }

                // Directory is valid so set the directory path
                options->repo_path = optarg;
                options->c_flag = true;
                break;
            
            case 'n':

                // Check if the n_flag was previously turned on
                if ((true == options->n_flag) || (false == options->c_flag))
                {
                    usage(program_name);
                    exit_code = E_INVALID_INPUT;
                    print_exit_message(exit_code);
                    goto END;
                }

                options->n_flag = true;
                options->prog_names = calloc(argc, sizeof(char **)); // Array for storing program names
                options->num_prog_names = 0;
                optind--;
                size_t idx = 0;

                // Allow an unlimited number of program names
                while (optind < argc)
                {
                    if (NULL != strstr(argv[optind], "-"))
                    {
                        break;
                    }

                    options->prog_names[idx] = argv[optind];
                    options->num_prog_names += 1;
                    idx++;
                    optind++;
                }
                break;
            
            case 'h':
                help(program_name);
                goto END;

            case '?':
            default:
                fprintf(stderr, "\nOption '-%c' not supported\n", optopt);
                usage(program_name);
                exit_code = E_INVALID_INPUT;
                goto END;
        }
    }

    // // Set the directory path only if it exists
    // char *directory;
    // if (optind <= argc)
    // {
    //     directory = argv[optind-1];
    //     // Check if the directory exists
    //     exit_code = directory_exists(directory);
    //     if (exit_code != E_DIRECTORY_EXISTS)
    //     {
    //         print_exit_message(exit_code);
    //         goto END;
    //     }

    //     // Directory is valid so set the directory path
    //     options->repo_path = directory;
    // }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}
