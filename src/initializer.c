#include "initializer.h"

struct src_paths
{
    // Level 1 Directories
    const char *dir_repo_generator;

    // Level 2 Directories
    const char *dir_save_data;
    const char *dir_c;
    const char *dir_python;

    // Level 3 Directories
    const char *dir_src;
    const char *dir_include;
    const char *dir_docs;
    const char *dir_test;

    // Files
    const char *file_test;
    const char *file_test_all;
    const char *file_makefile;
    const char *file_main_c;
    const char *file_main_h;
    const char *file_exit_codes_c;
    const char *file_exit_codes_h;
};

struct dest_paths
{
    // Directories
    const char *dir_src;
    const char *dir_include;
    const char *dir_docs;
    const char *dir_test;

    // Files
    const char *file_test;
    const char *file_makefile;
    const char *file_main_c;
    const char *file_main_h;
    const char *file_exit_codes_c;
    const char *file_exit_codes_h;
};

exit_code_t initialize_repo(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    src_paths_t *src_paths = calloc(1, sizeof(src_paths)); // Create a new source paths struct
    dest_paths_t *dest_paths = calloc(1, sizeof(dest_paths)); // Create a new destination paths struct

    const char *path = options->repo_path;

    if (NULL == path)
    {
        exit_code = E_NULL_POINTER;
        print_exit_message(exit_code);
        goto END;
    }
    printf("\n----------------NOTICE----------------\n");
    char message[256] = "";
    strcpy(message, "This will initialize the following path as a C repository:\n\nREPOSITORY: [");
    strcat(message, path);
    strcat(message, "]\n\nDo you wish to continue? [Y]/[N] ");

    // Check if the user wants to initialize the input path as a C repository
    exit_code = get_input_yes_no(stdin, message);
    if (E_YES != exit_code)
    {
        goto END;
    }

    exit_code = initialize_save_data(options, src_paths);
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

exit_code_t initialize_save_data(options_t *options, src_paths_t *src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // Get the user's home directory
    const char *home = (const char*)getenv("HOME");

    // Create repo_generator path
    src_paths->dir_repo_generator = append_path(home, "repo_generator");

    // Create save_data path
    src_paths->dir_save_data = append_path(src_paths->dir_repo_generator, "save_data");

    // Check if the save_data directory exists
    exit_code = directory_exists(src_paths->dir_repo_generator);
    if (E_DIRECTORY_EXISTS != exit_code)
    {   
        printf("\n----------------NOTICE----------------\n");
        char message[512] = "";
        strcpy(message, "No save data found...\nTo continue, a new save directory must be initialized.\n");
        strcat(message, "A new save directory will be created at the following location:\n\nSAVE DIRECTORY: [");
        strcat(message, src_paths->dir_save_data);
        strcat(message, "]\n\nDo you wish to continue? [Y]/[N] ");

        // Check if the user wants to initialize the input path as a C repository
        exit_code = get_input_yes_no(stdin, message);
        if (E_YES != exit_code)
        {
            goto END;
        }

        printf("\n------INITIALIZING SAVE DIRECTORY------\n");

        // Create the repo_initializer directory if it doesn't exist
        exit_code = create_directory(src_paths->dir_repo_generator);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }

        exit_code = create_directory(src_paths->dir_save_data);
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

    // Attempt to read from save file
    //exit_code = copy_file(dest_paths->main)

    // If it doesn't exist create one
    printf("---------------------------------------------------------------\n");
    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_src_directories(src_paths_t *src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    //-----DIRECTORY PATHS-----

    // Create level 1 directory paths
    src_paths->dir_c = append_path(src_paths->dir_save_data, "C");

    // Create level 2 directory paths
    src_paths->dir_src = append_path(src_paths->dir_c, "src");
    src_paths->dir_include = append_path(src_paths->dir_c, "include");
    src_paths->dir_docs = append_path(src_paths->dir_c, "docs");
    src_paths->dir_test = append_path(src_paths->dir_c, "test");
    
    // Check if the 'C' subdirectory exists
    exit_code = directory_exists(src_paths->dir_c);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'C' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_c);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if the 'src' subdirectory exists
    exit_code = directory_exists(src_paths->dir_src);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'src' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_src);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if the 'include' subdirectory exists
    exit_code = directory_exists(src_paths->dir_include);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'include' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_include);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if the 'docs' subdirectory exists
    exit_code = directory_exists(src_paths->dir_docs);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'docs' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_docs);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if the 'test' subdirectory exists
    exit_code = directory_exists(src_paths->dir_test);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'test' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_test);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_src_files(src_paths_t *src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    //-----FILE PATHS-----

    // Create source file paths
    src_paths->file_main_c = append_path(src_paths->dir_src, "main.c");
    src_paths->file_main_h = append_path(src_paths->dir_include, "main.h");
    src_paths->file_exit_codes_c = append_path(src_paths->dir_src, "exit_codes.c");
    src_paths->file_exit_codes_h = append_path(src_paths->dir_include, "exit_codes.h");
    src_paths->file_test = append_path(src_paths->dir_test, "test.c");
    src_paths->file_test_all = append_path(src_paths->dir_test, "test_all.c");

    // Check if 'main.c' exists
    exit_code = file_exists(src_paths->file_main_c);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'main.c' if it doesn't exist
        exit_code = create_file(src_paths->file_main_c, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if 'main.h' exists
    exit_code = file_exists(src_paths->file_main_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'main.h' if it doesn't exist
        exit_code = create_file(src_paths->file_main_h, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if 'main.h' exists
    exit_code = file_exists(src_paths->file_main_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'main.h' if it doesn't exist
        exit_code = create_file(src_paths->file_main_h, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if 'exit_codes.c' exists
    exit_code = file_exists(src_paths->file_exit_codes_c);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'exit_codes.c' if it doesn't exist
        exit_code = create_file(src_paths->file_exit_codes_c, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if 'exit_codes.h' exists
    exit_code = file_exists(src_paths->file_exit_codes_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'exit_codes.h' if it doesn't exist
        exit_code = create_file(src_paths->file_exit_codes_h, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if 'test.c' exists
    exit_code = file_exists(src_paths->file_test);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'test.c' if it doesn't exist
        exit_code = create_file(src_paths->file_test, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

    // Check if 'test_all.c' exists
    exit_code = file_exists(src_paths->file_test_all);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'test_all.c' if it doesn't exist
        exit_code = create_file(src_paths->file_test_all, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }

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