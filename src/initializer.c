#include "initializer.h"

struct path_list
{
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

exit_code_t initialize_repo(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == path)
    {
        exit_code = E_NULL_POINTER;
        print_exit_message(exit_code);
        goto END;
    }

    char abort_msg[] = "\nCtrl + C detected.\nAborting...\n";

    printf("This will initialize the following path as a C repository:\n%s\n\nDo you wish to continue? [Y]/[N]\n", path);

    char input = '\0';

    while ('y' != input)
    {
        input = fgetc(stdin);

        // Check for SIGINT (Ctrl + C)
        if (true == abort_program)
        {
            write(2, abort_msg, strlen(abort_msg));
            goto END;
        }

        input = tolower(input);

        if ('y' == input)
        {
            exit_code = E_SUCCESS;
            break;
        }

        else if ('n' == input)
        {
            printf("exiting...\n");
            exit_code = E_SUCCESS;
            goto END;
        }
        else
        {
            printf("Please enter [Y] to continue or [N] to exit\n");
        }
    }

    exit_code = create_directories(path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_gitignore(path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_makefile(path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_exit_codes(path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_main(path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_directories(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *directory_path = NULL;

    directory_path = append_path(path, "src");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    directory_path = append_path(path, "include");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    directory_path = append_path(path, "docs");

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    directory_path = append_path(path, "test");

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

exit_code_t create_gitignore(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *gitignore = generate_gitignore();

    file_path = append_path(path, ".gitignore");

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

exit_code_t create_makefile(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *Makefile = generate_makefile();

    file_path = append_path(path, "Makefile");

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

exit_code_t create_exit_codes(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *exit_codes_c = generate_exit_codes_c();
    const char *exit_codes_h = generate_exit_codes_h();

    file_path = append_path(path, "src/exit_codes.c");

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

    file_path = append_path(path, "include/exit_codes.h");

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

exit_code_t create_main(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char *file_path = NULL;

    const char *main_c = generate_main_c();
    const char *main_h = generate_main_h();

    file_path = append_path(path, "src/main.c");

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

    file_path = append_path(path, "src/main.h");
    
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