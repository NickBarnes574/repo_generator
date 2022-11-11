#include "initializer.h"

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
    // TODO: remove all generated content from repo if initialization fails
    return exit_code;
}

exit_code_t create_directories(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char directory_path [1024];

    strcpy(directory_path, path);
    strncat(directory_path, "/src", 5);

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    strcpy(directory_path, path);
    strncat(directory_path, "/include", 9);

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    strcpy(directory_path, path);
    strncat(directory_path, "/docs", 6);

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    strcpy(directory_path, path);
    strncat(directory_path, "/test", 6);

    exit_code = create_directory(directory_path);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_gitignore(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char file_path [1024];

    const char *gitignore = generate_gitignore();

    strcpy(file_path, path);
    strncat(file_path, "/.gitignore", 12);

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
    return exit_code;
}

exit_code_t create_makefile(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char file_path [1024];

    const char *Makefile = generate_makefile();

    strcpy(file_path, path);
    strncat(file_path, "/Makefile", 10);

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
    return exit_code;
}

exit_code_t create_exit_codes(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char file_path [1024];

    const char *exit_codes_c = generate_exit_codes_c();
    const char *exit_codes_h = generate_exit_codes_h();

    strcpy(file_path, path);
    strncat(file_path, "/src/exit_codes.c", 18);

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

    strcpy(file_path, path);
    strncat(file_path, "/include/exit_codes.h", 22);

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
    return exit_code;
}

exit_code_t create_main(const char *path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    char file_path [1024];

    const char *main_c = generate_main_c();
    const char *main_h = generate_main_h();

    strcpy(file_path, path);
    strncat(file_path, "/src/main.c", 12);

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

    strcpy(file_path, path);
    strncat(file_path, "/include/main.h", 16);
    
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
    return exit_code;
}