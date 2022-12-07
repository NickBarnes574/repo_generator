#include "initializer.h"

exit_code_t initialize_repo(options_t *options, char **src_paths, char **dest_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if ((NULL == options) || (NULL == src_paths))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // Create an initialization message
    char msg_init_repo[1024] = "";
    strcpy(msg_init_repo, "\nProject Type: ");

    // Create a C project
    if (true == options->c_flag)
    {
        strcat(msg_init_repo, C);
    }

    // Create a Python project
    if (true == options->p_flag)
    {
        strcat(msg_init_repo, PYTHON);
    }

    strcat(msg_init_repo, "\nProject files will be generated in the following directory:\n\nPROJECT FOLDER: [");
    strcat(msg_init_repo, dest_paths[DEST_DIR_REPO]);
    strcat(msg_init_repo, "]\n\nDo you wish to continue? [Y]/[N] ");

    // Check if the user wants to initialize the input path as a C repository
    exit_code = get_input_yes_no(stdin, msg_init_repo);
    if (E_YES != exit_code)
    {
        goto END;
    }

    // Initialize save directory
    exit_code = initialize_save_directory(options, src_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize source data
    exit_code = initialize_source_data(options, src_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize destination data
    exit_code = initialize_destination_data(options, dest_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t initialize_save_directory(options_t *options, char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if ((NULL == options) || (NULL == src_paths))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    exit_code = directory_exists(src_paths[SRC_DIR_REPO]);

    // Create a save directory message
    char msg_save_dir[1024] = "";
    strcpy(msg_save_dir, "\nNOTICE: [NO SAVE DATA FOUND]\n\n");
    strcat(msg_save_dir, "To continue, a new save directory must be initialized.\n");
    strcat(msg_save_dir, "A new save directory will be created at the following location:\n\nSAVE DIRECTORY: [");
    strcat(msg_save_dir, src_paths[SRC_DIR_SAVE_DATA]);
    strcat(msg_save_dir, "]\n\nDo you wish to continue? [Y]/[N] ");

    // Check if the user wants to create a save directory
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        exit_code = get_input_yes_no(stdin, msg_save_dir);
        if (E_YES != exit_code)
        {
            goto END;
        }

        // Print initialization message
        fprintf(stdout, "%s", "\nInitializing save directory...\n");

        // Create the repo_generator directory if it doesn't exist
        exit_code = create_directory(src_paths[SRC_DIR_REPO]);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
        //print_leader_line(stdout, "DIRECTORY", src_paths[SRC_DIR_REPO], "OK");

        // Create the save_data directory if it doesn't exist
        exit_code = create_directory(src_paths[SRC_DIR_SAVE_DATA]);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
        //print_leader_line(stdout, "DIRECTORY", src_paths[SRC_DIR_SAVE_DATA], "OK");
    }
    else
    {
        fprintf(stdout, "%s", "\n[SAVE DIRECTORY FOUND]\n");
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t initialize_source_data(options_t *options, char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if ((NULL == options) || (NULL == src_paths))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // Check if the 'C' subdirectory exists within the save_data directory
    if (true == options->c_flag)
    {
        exit_code = init_c_src_directories(src_paths);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }

        exit_code = init_c_src_files(src_paths, options);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

END:
    return exit_code;
}

exit_code_t initialize_destination_data(options_t *options, char **dest_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if ((NULL == options) || (NULL == dest_paths))
    {
        goto END;
    }

    if (true == options->c_flag)
    {
        exit_code = init_c_dest_directories(dest_paths, options);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }

        exit_code = init_c_dest_files(dest_paths, options);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t initialize_directory(char *path, bool disp_result)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == path)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char result[5] = "FAIL";

    // Check if the directory exists
    exit_code = directory_exists(path);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the directory if it does not exist
        exit_code = create_directory(path);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    strcpy(result, "OK");
    exit_code = E_SUCCESS;
END:
    if (true == disp_result)
    {
        print_leader_line(stdout, "DIRECTORY", path, result);
    }
    return exit_code;
}

exit_code_t initialize_file(char *path, const char *contents, bool disp_result)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if ((NULL == path) || (NULL == contents))
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char result[5] = "FAIL";

    // Check if the file exists
    exit_code = file_exists(path);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create the file if it does not exist
        exit_code = create_file(path, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }

        // Write the contents to the file
        exit_code = write_to_file(path, contents);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }

    strcpy(result, "OK");
    exit_code = E_SUCCESS;
END:
    if (true == disp_result)
    {
        print_leader_line(stdout, "FILE", path, result);
    }
    return exit_code;
}

exit_code_t init_c_src_directories(char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == src_paths)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    printf("Initializing source directories...\n");

    // Initialize 'C' directory
    exit_code = initialize_directory(src_paths[SRC_DIR_C], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'src' directory
    exit_code = initialize_directory(src_paths[SRC_DIR_SRC], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'include' directory
    exit_code = initialize_directory(src_paths[SRC_DIR_INCLUDE], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'docs' directory
    exit_code = initialize_directory(src_paths[SRC_DIR_DOCS], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'test' directory
    exit_code = initialize_directory(src_paths[SRC_DIR_TEST], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'templates' directory
    exit_code = initialize_directory(src_paths[SRC_DIR_TEMPLATES], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_src_files(char **src_paths, options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == src_paths)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    printf("Initializing source files...\n");

    const char *main_c = generate_main_c();
    const char *main_h = generate_main_h();
    const char *exit_c = generate_exit_codes_c();
    const char *exit_h = generate_exit_codes_h();
    const char *test_c = generate_test_c();
    const char *test_all_c = generate_test_all_c();
    char *def_makefile = generate_makefile(options);
    const char *gitignore = generate_gitignore();

    // Initialize 'main.c'
    exit_code = initialize_file(src_paths[SRC_FILE_MAIN_C], main_c, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'main.h'
    exit_code = initialize_file(src_paths[SRC_FILE_MAIN_H], main_h, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'exit_c'
    exit_code = initialize_file(src_paths[SRC_FILE_EXIT_CODES_C], exit_c, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'exit_h'
    exit_code = initialize_file(src_paths[SRC_FILE_EXIT_CODES_H], exit_h, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'tests.c'
    exit_code = initialize_file(src_paths[SRC_FILE_TESTS], test_c, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'test_all.c'
    exit_code = initialize_file(src_paths[SRC_FILE_TEST_ALL], test_all_c, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize default 'Makefile'
    exit_code = initialize_file(src_paths[SRC_FILE_DEF_MAKEFILE], def_makefile, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize '.gitignore'
    exit_code = initialize_file(src_paths[SRC_FILE_GITIGNORE], gitignore, false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(def_makefile);
    return exit_code;
}

exit_code_t init_c_dest_directories(char **dest_paths, options_t *options)
{
    //DEBUG
    (void)options;
    //DEBUG
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == dest_paths)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    printf("Initializing destination directories...\n");

    // Initialize 'repo' directory
    exit_code = initialize_directory(dest_paths[DEST_DIR_REPO], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'src' directory
    exit_code = initialize_directory(dest_paths[DEST_DIR_SRC], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // // Generate 'src' sub directories if any program names were passed on the command line
    // if (options->num_prog_names > 0)
    // {
    //     for (size_t idx = 0; idx < options->num_prog_names; idx++)
    //     {
    //         char *custom_directory = append_path(dest_paths[DEST_DIR_SRC], options->prog_names[idx]);
    //         exit_code = initialize_directory(custom_directory, false);
    //         free(custom_directory);
    //         if (E_SUCCESS != exit_code)
    //         {
    //             goto END;
    //         }
    //     }
    // }

    // Initialize 'include' directory
    exit_code = initialize_directory(dest_paths[DEST_DIR_INCLUDE], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // // Generate 'include' sub directories if any program names were passed on the command line
    // if (options->num_prog_names > 0)
    // {
    //     for (size_t idx = 0; idx < options->num_prog_names; idx++)
    //     {
    //         char *custom_directory = append_path(dest_paths[DEST_DIR_INCLUDE], options->prog_names[idx]);
    //         exit_code = initialize_directory(custom_directory, false);
    //         free(custom_directory);
    //         if (E_SUCCESS != exit_code)
    //         {
    //             goto END;
    //         }
    //     }
    // }

    // Initialize 'docs' directory
    exit_code = initialize_directory(dest_paths[DEST_DIR_DOCS], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'test' directory
    exit_code = initialize_directory(dest_paths[DEST_DIR_TEST], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'templates' directory
    exit_code = initialize_directory(dest_paths[DEST_DIR_TEMPLATES], false);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_dest_files(char **dest_paths, options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == dest_paths)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    printf("\n---------GENERATING PROJECT FILES--------\n");

    const char *main_c = generate_main_c();
    const char *main_h = generate_main_h();
    const char *exit_c = generate_exit_codes_c();
    const char *exit_h = generate_exit_codes_h();
    const char *test_c = generate_test_c();
    const char *test_all_c = generate_test_all_c();
    char *def_makefile = generate_makefile(options);
    char *custom_test_all = generate_custom_test_all_c(options);
    const char *gitignore = generate_gitignore();

    if (options->num_prog_names > 0)
    {
        // Generate main.c inside 'src' sub directories if any program names were passed on the command line
        if (options->num_prog_names >= 2)
        {
            char **main_file_contents = calloc(options->num_prog_names, sizeof(char**));
            char **test_file_contents = calloc(options->num_prog_names, sizeof(char**));
            for (size_t idx = 0; idx < options->num_prog_names; idx++)
            {
                // Create the 'src/prog_name' paths
                char *custom_dir_src = append_path(dest_paths[DEST_DIR_SRC], options->prog_names[idx]);
                exit_code = initialize_directory(custom_dir_src, false);

                // Create the custom 'main.c' files for each program
                char *custom_file_src = append_path(custom_dir_src, "main.c");
                main_file_contents[idx] = generate_custom_main_c(options, idx);
                exit_code = initialize_file(custom_file_src, main_file_contents[idx], true);

                // Create the 'include/prog_name' paths
                char *custom_dir_include = append_path(dest_paths[DEST_DIR_INCLUDE], options->prog_names[idx]);
                exit_code = initialize_directory(custom_dir_include, false);

                // Create the 'main.h' files for each program
                char *custom_file_include = append_path(custom_dir_include, "main.h");
                exit_code = initialize_file(custom_file_include, main_h, true);

                // Create the test files for each program
                char temp[300] = "";
                strcpy(temp, options->prog_names[idx]);
                strcat(temp, "_tests.c");
                char *custom_file_test = append_path(dest_paths[DEST_DIR_TEST], temp);
                test_file_contents[idx] = generate_custom_test_c(options, idx);
                exit_code = initialize_file(custom_file_test, test_file_contents[idx], true);

                free(custom_dir_src);
                free(custom_file_src);
                free(custom_dir_include);
                free(custom_file_include);
                free(custom_file_test);
                free(main_file_contents[idx]);
                free(test_file_contents[idx]);
                if (E_SUCCESS != exit_code)
                {
                    goto END;
                }
            }

            // Create the test all
            exit_code = initialize_file(dest_paths[DEST_FILE_TEST_ALL], custom_test_all, true);
            free(main_file_contents);
            free(test_file_contents);
        }

        else
        {
            // Initialize 'main.c'
            exit_code = initialize_file(dest_paths[DEST_FILE_MAIN_C], main_c, true);
            if (E_SUCCESS != exit_code)
            {
                goto END;
            }

            // Initialize 'main.h'
            exit_code = initialize_file(dest_paths[DEST_FILE_MAIN_H], main_h, true);
            if (E_SUCCESS != exit_code)
            {
                goto END;
            }

            // Initialize 'tests.c'
            exit_code = initialize_file(dest_paths[DEST_FILE_TESTS], test_c, true);
            if (E_SUCCESS != exit_code)
            {
                goto END;
            }

            // Initialize 'test_all.c'
            exit_code = initialize_file(dest_paths[DEST_FILE_TEST_ALL], test_all_c, true);
            if (E_SUCCESS != exit_code)
            {
                goto END;
            }
        }
    }

    else
    {
        // Initialize 'main.c'
        exit_code = initialize_file(dest_paths[DEST_FILE_MAIN_C], main_c, true);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }

        // Initialize 'main.h'
        exit_code = initialize_file(dest_paths[DEST_FILE_MAIN_H], main_h, true);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }

        // Initialize 'tests.c'
        exit_code = initialize_file(dest_paths[DEST_FILE_TESTS], test_c, true);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    
        // Initialize 'test_all.c'
        exit_code = initialize_file(dest_paths[DEST_FILE_TEST_ALL], test_all_c, true);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }

    // Initialize 'exit_c'
    exit_code = initialize_file(dest_paths[DEST_FILE_EXIT_CODES_C], exit_c, true);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'exit_h'
    exit_code = initialize_file(dest_paths[DEST_FILE_EXIT_CODES_H], exit_h, true);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'test_all.c'
    exit_code = initialize_file(dest_paths[DEST_FILE_TEST_ALL], test_all_c, true);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize default 'Makefile'
    exit_code = initialize_file(dest_paths[DEST_FILE_DEF_MAKEFILE], def_makefile, true);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize '.gitignore'
    exit_code = initialize_file(dest_paths[DEST_FILE_GITIGNORE], gitignore, true);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    free(def_makefile);
    free(custom_test_all);
    return exit_code;
}