#include "initializer.h"

struct path_list
{
    // Repo initializer
    const char *repo_initializer;
    const char *save_data;
    const char *c;
    const char *python;

    // Directories
    const char *src;
    const char *include;
    const char *docs;

    // Files
    const char *test;
    const char *makefile;
    const char *main_c;
    const char *main_h;
    const char *exit_codes_c;
    const char *exit_codes_h;
};

exit_code_t initialize_repo(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    path_list_t *path_list = calloc(1, sizeof(path_list)); // Create a new path list

    const char *path = options->repo_path;

    if (NULL == path)
    {
        exit_code = E_NULL_POINTER;
        print_exit_message(exit_code);
        goto END;
    }

    char abort_msg[] = "\nCtrl + C detected.\nAborting...\n";

    printf("This will initialize the following path as a C repository:\n%s\n\nDo you wish to continue? [Y]/[N]\n", path);

    char *input = calloc(1, sizeof(char *));

    while (strcmp("y", input) != 0)
    {
        input = read_line(stdin, input);

        // Check for SIGINT (Ctrl + C)
        if (true == abort_program)
        {
            write(2, abort_msg, strlen(abort_msg));
            free(input);
            goto END;
        }

        for (size_t idx = 0; idx < strlen(input); idx++)
        {
            input[idx] = tolower(input[idx]);
        }

        if (strcmp("y", input) == 0)
        {
            free(input);
            exit_code = E_SUCCESS;
            break;
        }

        else if (strcmp("n", input) == 0)
        {
            printf("exiting...\n");
            free(input);
            exit_code = E_SUCCESS;
            goto END;
        }
        else
        {
            printf("Please enter [Y] to continue or [N] to exit\n");
        }
    }

    exit_code = initialize_save_data(options, path_list);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_directories(options);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Line to separate directories and files
    printf("---------------------------------------------------------------\n");

    exit_code = create_gitignore(options);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_makefile(options);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_exit_codes(options);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_main(options);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t initialize_save_data(options_t *options, path_list_t *path_list)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // Get the user's home directory
    const char *home = (const char*)getenv("HOME");

    // Create repo_initializer path
    path_list->repo_initializer = append_path(home, "repo_initializer");
    printf("%s\n", path_list->repo_initializer);

    // Create save_data path
    path_list->save_data = append_path(path_list->repo_initializer, "save_data");
    printf("%s\n", path_list->save_data);

    // Check if the save_data directory exists
    exit_code = directory_exists(path_list->repo_initializer);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        char abort_msg[] = "\nCtrl + C detected.\nAborting...\n";

        printf("NOTICE: No save data found...\nTo continue, a new save directory must be initialized.\n\
        A new save directory will be created at the following location:\n%s\
                \nDo you wish to continue? [Y]/[N]\n", path_list->save_data);

        char *input = calloc(1, sizeof(char *));

        while (strcmp("y", input) != 0)
        {
            input = read_line(stdin, input);

            // Check for SIGINT (Ctrl + C)
            if (true == abort_program)
            {
                write(2, abort_msg, strlen(abort_msg));
                free(input);
                goto END;
            }

            for (size_t idx = 0; idx < strlen(input); idx++)
            {
                input[idx] = tolower(input[idx]);
            }

            if (strcmp("y", input) == 0)
            {
                free(input);
                exit_code = E_SUCCESS;
                break;
            }

            else if (strcmp("n", input) == 0)
            {
                printf("exiting...\n");
                free(input);
                exit_code = E_SUCCESS;
                goto END;
            }
            else
            {
                printf("Please enter [Y] to continue or [N] to exit\n");
            }
        }

        printf("------INITIALIZING SAVE DIRECTORY------\n");

        // Create the repo_initializer directory if it doesn't exist
        exit_code = create_directory(path_list->repo_initializer);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }

        exit_code = create_directory(path_list->save_data);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    else
    {
        printf("------SAVE DIRECTORY FOUND------\n");
    }

    // Check if the 'C' subdirectory exists within the save_data directory
    if (true == options->c_flag)
    {
        // Create C path
        path_list->c = append_path(path_list->save_data, "C");

        // Check if the 'C' subdirectory exists
        exit_code = directory_exists(path_list->c);
        if (E_DIRECTORY_EXISTS != exit_code)
        {
            // Create the 'C' subdirectory if it doesn't exist
            exit_code = create_directory(path_list->c);
            if (E_SUCCESS != exit_code)
            {
                print_exit_message(exit_code);
                goto END;
            }
        }
    }
    // Attempt to read from save file
    // If it doesn't exist create one
    printf("---------------------------------------------------------------\n");
    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_directories(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *directory_path = NULL;

    directory_path = append_path(options->repo_path, "src");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    directory_path = append_path(options->repo_path, "include");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    directory_path = append_path(options->repo_path, "docs");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    directory_path = append_path(options->repo_path, "test");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(directory_path);
    return exit_code;
}

exit_code_t create_gitignore(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *gitignore = generate_gitignore();

    file_path = append_path(options->repo_path, ".gitignore");

    exit_code = create_file(file_path, "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(file_path, gitignore);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(file_path);
    return exit_code;
}

exit_code_t create_makefile(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *Makefile = generate_makefile();

    file_path = append_path(options->repo_path, "Makefile");

    exit_code = create_file(file_path, "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(file_path, Makefile);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(file_path);
    return exit_code;
}

exit_code_t create_exit_codes(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *exit_codes_c = generate_exit_codes_c();
    const char *exit_codes_h = generate_exit_codes_h();

    file_path = append_path(options->repo_path, "src/exit_codes.c");

    exit_code = create_file(file_path, "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(file_path, exit_codes_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    file_path = append_path(options->repo_path, "include/exit_codes.h");

    exit_code = create_file(file_path, "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(file_path, exit_codes_h);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(file_path);
    return exit_code;
}

exit_code_t create_main(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *main_c = generate_main_c();
    const char *main_h = generate_main_h();

    file_path = append_path(options->repo_path, "src/main.c");

    exit_code = create_file(file_path, "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(file_path, main_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    file_path = append_path(options->repo_path, "src/main.h");
    
    exit_code = create_file(file_path, "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(file_path, main_h);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(file_path);
    return exit_code;
}