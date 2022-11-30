#include "initializer.h"

exit_code_t initialize_repo(options_t *options, char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // Check if the user wants to initialize the input path as a C repository
    exit_code = get_input_yes_no(stdin, msg_init_repo(src_paths));
    if (E_YES != exit_code)
    {
        goto END;
    }

    // Initialize save data
    exit_code = initialize_save_data(options, src_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t initialize_save_data(options_t *options, char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // Check if the save_data directory exists
    fprintf(stdout, msg_check_save_dir());
    exit_code = directory_exists(src_paths[DIR_REPO]);

    // Check if the user wants to create a save directory
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        get_input_yes_no(stdin, msg_init_save_data(src_paths));
        if (E_YES != exit_code)
        {
            goto END;
        }
    }

    // Print initialization message
    fprintf(stdout, msg_init_save_dir());

    // Create the repo_generator directory if it doesn't exist
    exit_code = create_directory(src_paths[DIR_REPO]);
    if (E_SUCCESS != exit_code)
    {
        print_exit_message(exit_code);
        goto END;
    }

    // Create the save_data directory if it doesn't exist
    exit_code = create_directory(src_paths[DIR_SAVE_DATA]);
    if (E_SUCCESS != exit_code)
    {
        print_exit_message(exit_code);
        goto END;
    }

    print_leader_line(stdout, "DIRECTORY", src_paths[DIR_REPO], "OK");
    print_leader_line(stdout, "DIRECTORY", src_paths[DIR_SAVE_DATA], "OK");

    // Check if the 'C' subdirectory exists within the save_data directory
    if (true == options->c_flag)
    {
        exit_code = init_c_src_directories(src_paths);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }

        exit_code = init_c_src_files(src_paths);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

END:
    return exit_code;
}

exit_code_t initialize_directory(char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

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
    print_leader_line(stdout, "DIRECTORY", path, result);
    return exit_code;
}

exit_code_t initialize_file(char *path, const char *contents)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

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
    print_leader_line(stdout, "FILE", path, result);
    return exit_code;
}

exit_code_t init_c_src_directories(char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    printf("\n------INITIALIZING SOURCE DIRECTORIES------\n");

    // Initialize 'C' directory
    exit_code = initialize_directory(src_paths[DIR_C]);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'src' directory
    exit_code = initialize_directory(src_paths[DIR_SRC]);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'include' directory
    exit_code = initialize_directory(src_paths[DIR_INCLUDE]);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'docs' directory
    exit_code = initialize_directory(src_paths[DIR_DOCS]);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'test' directory
    exit_code = initialize_directory(src_paths[DIR_TEST]);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'templates' directory
    exit_code = initialize_directory(src_paths[DIR_TEMPLATES]);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_src_files(char **src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    printf("\n---------INITIALIZING SOURCE FILES--------\n");

    const char *main_c = generate_main_c();
    const char *main_h = generate_main_h();
    const char *exit_c = generate_exit_codes_c();
    const char *exit_h = generate_exit_codes_h();
    //const char *test_c = generate_test_c();
    //const char *test_all = generate_test_all_c();
    const char *def_makefile = generate_makefile_single_program();
    const char *gitignore = generate_gitignore();

    // Initialize 'main.c'
    exit_code = initialize_file(src_paths[FILE_MAIN_C], main_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'main.h'
    exit_code = initialize_file(src_paths[FILE_MAIN_C], main_h);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'exit_c'
    exit_code = initialize_file(src_paths[FILE_EXIT_CODES_C], exit_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'exit_h'
    exit_code = initialize_file(src_paths[FILE_EXIT_CODES_H], exit_h);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'tests.c'
    exit_code = initialize_file(src_paths[FILE_TESTS], test_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize 'test_all.c'
    exit_code = initialize_file(src_paths[FILE_TEST_ALL], test_all_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize default 'Makefile'
    exit_code = initialize_file(src_paths[FILE_DEF_MAKEFILE], def_makefile);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    // Initialize '.gitignore'
    exit_code = initialize_file(src_paths[FILE_GITIGNORE], gitignore);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}