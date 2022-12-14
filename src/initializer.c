#include "initializer.h"

// TODO: Turn src_paths struct into char** in order to allow any number of destination paths to be implemented
struct src_paths
{
    // Level 1 Directories
    char *dir_repo_generator;

    // Level 2 Directories
    char *dir_save_data;

    // Level 3 Directories
    char *dir_c;
    char *dir_python;

    // Level 4 Directories
    char *dir_src;
    char *dir_include;
    char *dir_docs;
    char *dir_test;
    char *dir_templates;
    char *dir_makefiles;

    // Level 5 Directories
    char *dir_makefile_single;

    // Files
    char *file_test;
    char *file_test_all;
    char *file_makefile_single;
    char *file_main_c;
    char *file_main_h;
    char *file_exit_codes_c;
    char *file_exit_codes_h;
    char *file_gitignore;
};

// TODO: Turn dest_paths struct into char** in order to allow any number of destination paths to be implemented
struct dest_paths
{
    // Level 1 Directories
    char *dir_repo;

    // Level 2 Directories
    char *dir_src;
    char *dir_include;
    char *dir_docs;
    char *dir_test;
    char *dir_templates;
    char *dir_makefiles;

    // Level 3 Directories
    char *dir_makefile_single;

    // Files
    char *file_test;
    char *file_test_all;
    char *file_makefile_default;
    char *file_makefile_single;
    char *file_main_c;
    char *file_main_h;
    char *file_exit_codes_c;
    char *file_exit_codes_h;
    char *file_gitignore;
};

exit_code_t initialize_repo(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    src_paths_t *src_paths = calloc(1, sizeof(src_paths_t)); // Create a new source paths struct
    dest_paths_t *dest_paths = calloc(1, sizeof(dest_paths_t)); // Create a new destination paths struct
    if (NULL == src_paths || NULL == dest_paths)
    {
        exit_code = E_NULL_POINTER;
        print_exit_message(exit_code);
        goto END;
    }

    // const char *path = options->repo_path;
    dest_paths->dir_repo = options->repo_path;
    if (NULL == dest_paths->dir_repo)
    {
        exit_code = E_NULL_POINTER;
        print_exit_message(exit_code);
        goto END;
    }

    printf("\n----------------NOTICE----------------\n");
    char message[256] = "";
    strcpy(message, "This will initialize the following path as a C repository:\n\nREPOSITORY: [");
    strcat(message, (const char*)dest_paths->dir_repo);
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

    exit_code = init_c_dest_directories(dest_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = init_c_dest_files(dest_paths, src_paths);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:

    /***************************************
    Free source files and directories
    ****************************************/

    // Free file paths
    free(src_paths->file_exit_codes_c);
    free(src_paths->file_exit_codes_h);
    free(src_paths->file_main_c);
    free(src_paths->file_main_h);
    free(src_paths->file_test);
    free(src_paths->file_test_all);
    free(src_paths->file_makefile_single);
    free(src_paths->file_gitignore);

    // Free directory paths

    // Level 6 directories
    free(src_paths->dir_makefile_single);

    // Level 5 directories
    free(src_paths->dir_makefiles);

    // Level 4 directories
    free(src_paths->dir_docs);
    free(src_paths->dir_include);
    free(src_paths->dir_src);
    free(src_paths->dir_test);
    free(src_paths->dir_templates);

    // Level 3 directories
    free(src_paths->dir_save_data);

    // Level 2 directories
    free(src_paths->dir_c);
    free(src_paths->dir_python);

    // Level 1 directories
    free(src_paths->dir_repo_generator);

    /***************************************
    Free destination files and directories
    ****************************************/

    // Free file paths
    free(dest_paths->file_exit_codes_c);
    free(dest_paths->file_exit_codes_h);
    free(dest_paths->file_main_c);
    free(dest_paths->file_main_h);
    free(dest_paths->file_test);
    free(dest_paths->file_test_all);
    free(dest_paths->file_makefile_single);
    free(dest_paths->file_makefile_default);
    free(dest_paths->file_gitignore);

    // Free directory paths

    // Level 4 directories
    free(dest_paths->dir_makefile_single);

    // Level 3 directories
    free(dest_paths->dir_makefiles);

    // Level 2 directories
    free(dest_paths->dir_docs);
    free(dest_paths->dir_include);
    free(dest_paths->dir_src);
    free(dest_paths->dir_test);
    free(dest_paths->dir_templates);

    // Free structs
    free(src_paths);
    free(dest_paths);
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
    printf("\n--------CHECKING SAVE DIRECTORY--------\n");
    exit_code = directory_exists(src_paths->dir_repo_generator);
    if (E_DIRECTORY_EXISTS != exit_code)
    {   
        printf("\nNOTICE: [NO SAVE DATA FOUND]\n\n");
        char message[512] = "";
        strcpy(message, "To continue, a new save directory must be initialized.\n");
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
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_repo_generator, "OK");
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_save_data, "OK");

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
    src_paths->dir_templates = append_path(src_paths->dir_c, "templates");

    // Create level 3 directory paths
    src_paths->dir_makefiles = append_path(src_paths->dir_templates, "makefiles");

    // Create level 4 directory paths
    src_paths->dir_makefile_single = append_path(src_paths->dir_makefiles, "makefile_single");

    printf("\n------INITIALIZING SOURCE DIRECTORIES------\n");

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
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_c, "OK");

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
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_src, "OK");


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
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_include, "OK");


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
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_docs, "OK");


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
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_test, "OK");

    // Check if the 'templates' subdirectory exists
    exit_code = directory_exists(src_paths->dir_templates);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'templates' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_templates);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_templates, "OK");

    // Check if the 'makefiles' subdirectory exists
    exit_code = directory_exists(src_paths->dir_makefiles);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'makefiles' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_makefiles);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_makefiles, "OK");

    // Check if the 'makefile_single' subdirectory exists
    exit_code = directory_exists(src_paths->dir_makefile_single);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'makefile_single' subdirectory if it doesn't exist
        exit_code = create_directory(src_paths->dir_makefile_single);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", src_paths->dir_makefile_single, "OK");

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
    src_paths->file_makefile_single = append_path(src_paths->dir_makefile_single, "Makefile");
    src_paths->file_gitignore = append_path(src_paths->dir_c, ".gitignore");
    
    printf("\n---------INITIALIZING SOURCE FILES--------\n");

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

        const char *main_c = generate_main_c();
        exit_code = write_to_file(src_paths->file_main_c, main_c);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_main_c, "OK");

    // Check if 'main.h' exists
    exit_code = file_exists(src_paths->file_main_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'main.h' if it doesn't exist
        exit_code = create_file(src_paths->file_main_h, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("main.h\n");
            print_exit_message(exit_code);
            goto END;
        }

        const char *main_h = generate_main_h();
        exit_code = write_to_file(src_paths->file_main_h, main_h);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_main_h, "OK");

    // Check if 'exit_codes.c' exists
    exit_code = file_exists(src_paths->file_exit_codes_c);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'exit_codes.c' if it doesn't exist
        exit_code = create_file(src_paths->file_exit_codes_c, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("exit_codes.c\n");
            print_exit_message(exit_code);
            goto END;
        }

        const char *exit_c = generate_exit_codes_c();
        exit_code = write_to_file(src_paths->file_exit_codes_c, exit_c);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_exit_codes_c, "OK");

    // Check if 'exit_codes.h' exists
    exit_code = file_exists(src_paths->file_exit_codes_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'exit_codes.h' if it doesn't exist
        exit_code = create_file(src_paths->file_exit_codes_h, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("exit_codes.h\n");
            print_exit_message(exit_code);
            goto END;
        }

        const char *exit_h = generate_exit_codes_h();
        exit_code = write_to_file(src_paths->file_exit_codes_h, exit_h);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_exit_codes_h, "OK");

    // Check if 'test.c' exists
    exit_code = file_exists(src_paths->file_test);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'test.c' if it doesn't exist
        exit_code = create_file(src_paths->file_test, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("test.c\n");
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_test, "OK");

    // Check if 'test_all.c' exists
    exit_code = file_exists(src_paths->file_test_all);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'test_all.c' if it doesn't exist
        exit_code = create_file(src_paths->file_test_all, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("test_all.c\n");
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_test_all, "OK");

    // Check if Makefile single exists
    exit_code = file_exists(src_paths->file_makefile_single);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create Makefile single if it doesn't exist
        exit_code = create_file(src_paths->file_makefile_single, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("Makefile\n");
            print_exit_message(exit_code);
            goto END;
        }

        const char *makefile = generate_makefile_single_program();
        exit_code = write_to_file(src_paths->file_makefile_single, makefile);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_makefile_single, "OK");

    // Check if 'gitignore' exists
    exit_code = file_exists(src_paths->file_gitignore);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'gitignore' if it doesn't exist
        exit_code = create_file(src_paths->file_gitignore, "w");
        if (E_SUCCESS != exit_code)
        {
            printf(".gitignore\n");
            print_exit_message(exit_code);
            goto END;
        }

        const char *gitignore = generate_gitignore();
        exit_code = write_to_file(src_paths->file_gitignore, gitignore);
        if (E_SUCCESS != exit_code)
        {
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", src_paths->file_gitignore, "OK");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_dest_directories(dest_paths_t *dest_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    //-----DIRECTORY PATHS-----

    // Create level 2 directory paths
    dest_paths->dir_src = append_path(dest_paths->dir_repo, "src");
    dest_paths->dir_include = append_path(dest_paths->dir_repo, "include");
    dest_paths->dir_docs = append_path(dest_paths->dir_repo, "docs");
    dest_paths->dir_test = append_path(dest_paths->dir_repo, "test");
    dest_paths->dir_templates = append_path(dest_paths->dir_repo, "templates");
    dest_paths->dir_makefiles = append_path(dest_paths->dir_templates, "makefiles");
    dest_paths->dir_makefile_single = append_path(dest_paths->dir_makefiles, "makefile_single");

    printf("\n----CREATING DESTINATION DIRECTORIES----\n");

    // Check if the 'src' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_src);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'src' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_src);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_src, "OK");

    // Check if the 'include' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_include);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'include' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_include);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_include, "OK");

    // Check if the 'docs' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_docs);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'docs' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_docs);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_docs, "OK");

    // Check if the 'test' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_test);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'test' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_test);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_test, "OK");

    // Check if the 'templates' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_templates);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'templates' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_templates);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_templates, "OK");

    // Check if the 'makefiles' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_makefiles);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'makefiles' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_makefiles);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_makefiles, "OK");

    // Check if the 'makefile_single' subdirectory exists
    exit_code = directory_exists(dest_paths->dir_makefile_single);
    if (E_DIRECTORY_EXISTS != exit_code)
    {
        // Create the 'makefile_single' subdirectory if it doesn't exist
        exit_code = create_directory(dest_paths->dir_makefile_single);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "DIRECTORY", dest_paths->dir_makefile_single, "OK");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t init_c_dest_files(dest_paths_t *dest_paths, src_paths_t *src_paths)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    //-----FILE PATHS-----

    // Create source file paths
    dest_paths->file_main_c = append_path(dest_paths->dir_src, "main.c");
    dest_paths->file_main_h = append_path(dest_paths->dir_include, "main.h");
    dest_paths->file_exit_codes_c = append_path(dest_paths->dir_src, "exit_codes.c");
    dest_paths->file_exit_codes_h = append_path(dest_paths->dir_include, "exit_codes.h");
    dest_paths->file_test = append_path(dest_paths->dir_test, "test.c");
    dest_paths->file_test_all = append_path(dest_paths->dir_test, "test_all.c");
    dest_paths->file_makefile_default = append_path(dest_paths->dir_repo, "Makefile");
    dest_paths->file_makefile_single = append_path(dest_paths->dir_makefile_single, "Makefile");
    dest_paths->file_gitignore = append_path(dest_paths->dir_repo, ".gitignore");
    
    printf("\n-------CREATING DESTINATION FILES------\n");

    // Check if 'main.c' exists
    exit_code = file_exists(dest_paths->file_main_c);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'main.c' if it doesn't exist
        exit_code = create_file(dest_paths->file_main_c, "w");
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_main_c, (const char*)src_paths->file_main_c);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_main_c, "OK");

    // Check if 'main.h' exists
    exit_code = file_exists(dest_paths->file_main_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'main.h' if it doesn't exist
        exit_code = create_file(dest_paths->file_main_h, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("main.h\n");
            print_exit_message(exit_code);
            goto END;
        }
    
        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_main_h, (const char*)src_paths->file_main_h);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_main_h, "OK");

    // Check if 'exit_codes.c' exists
    exit_code = file_exists(dest_paths->file_exit_codes_c);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'exit_codes.c' if it doesn't exist
        exit_code = create_file(dest_paths->file_exit_codes_c, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("exit_codes.c\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_exit_codes_c, (const char*)src_paths->file_exit_codes_c);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_exit_codes_c, "OK");

    // Check if 'exit_codes.h' exists
    exit_code = file_exists(dest_paths->file_exit_codes_h);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'exit_codes.h' if it doesn't exist
        exit_code = create_file(dest_paths->file_exit_codes_h, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("exit_codes.h\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_exit_codes_h, (const char*)src_paths->file_exit_codes_h);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_exit_codes_h, "OK");

    // Check if 'test.c' exists
    exit_code = file_exists(dest_paths->file_test);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'test.c' if it doesn't exist
        exit_code = create_file(dest_paths->file_test, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("test.c\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_test, (const char*)src_paths->file_test);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_test, "OK");

    // Check if 'test_all.c' exists
    exit_code = file_exists(dest_paths->file_test_all);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'test_all.c' if it doesn't exist
        exit_code = create_file(dest_paths->file_test_all, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("test_all.c\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_test_all, (const char*)src_paths->file_test_all);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_test_all, "OK");

    // Check if default Makefile exists
    exit_code = file_exists(dest_paths->file_makefile_default);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create default Makefile if it doesn't exist
        exit_code = create_file(dest_paths->file_makefile_default, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("Makefile\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_makefile_default, (const char*)src_paths->file_makefile_single);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_makefile_default, "OK");

    // Check if Makefile single exists
    exit_code = file_exists(dest_paths->file_makefile_single);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create Makefile single if it doesn't exist
        exit_code = create_file(dest_paths->file_makefile_single, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("Makefile\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_makefile_single, (const char*)src_paths->file_makefile_single);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_makefile_default, "OK");

    // Check if 'gitignore' exists
    exit_code = file_exists(dest_paths->file_gitignore);
    if (E_FILE_EXISTS != exit_code)
    {
        // Create 'gitignore' if it doesn't exist
        exit_code = create_file(dest_paths->file_gitignore, "w");
        if (E_SUCCESS != exit_code)
        {
            printf("Makefile\n");
            print_exit_message(exit_code);
            goto END;
        }

        // Copy the contents from the source to the destination
        exit_code = copy_file((const char*)dest_paths->file_gitignore, (const char*)src_paths->file_gitignore);
        if (E_SUCCESS != exit_code)
        {
            print_exit_message(exit_code);
            goto END;
        }
    }
    print_leader_line(stdout, "FILE", dest_paths->file_gitignore, "OK");

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