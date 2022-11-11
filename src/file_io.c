#include "file_io.h"

exit_code_t file_exists(const char *filename)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if filename is NULL
    if (NULL == filename)
    {
        exit_code = E_NULL_POINTER;
        return exit_code;
    }

    // 2. Check if file exists
    if (access(filename, F_OK) == 0) // access() returns 0 upon success
    {
        exit_code = E_SUCCESS;
    }
    else
    {
        exit_code = E_FILE_DOES_NOT_EXIST;
    }

    return exit_code;
}

exit_code_t file_readable(const char *filename)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if filename is NULL
    if (NULL == filename)
    {
        exit_code = E_NULL_POINTER;
        return exit_code;
    }

    // 2. Check if file can be read
    if (access(filename, R_OK) == 0)
    {
        exit_code = E_SUCCESS;
    }
    else
    {
        exit_code = E_FILE_NOT_READABLE;
    }

    return exit_code;
}

exit_code_t validate_file(const char *filename)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if filename is NULL
    if (NULL == filename)
    {
        exit_code = E_NULL_POINTER;
        return exit_code;
    }

    // 2. Check if file does not exist
    exit_code = file_exists(filename);
    if (exit_code != E_SUCCESS)
    {
        return exit_code;
    }

    // 3. Check if file is not readable
    exit_code = file_readable(filename);
    if (exit_code != E_SUCCESS)
    {
        return exit_code;
    }

    exit_code = E_SUCCESS;
    return exit_code;
}

exit_code_t line_readable(FILE *file_ptr, char *buffer)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if file_ptr or buffer is NULL
    if (NULL == file_ptr || NULL == buffer)
    {
        exit_code = E_NULL_POINTER;
    }
    else
    {
        exit_code = E_SUCCESS;
    }

    return exit_code;
}

char *read_line(FILE *file_ptr, char *buffer)
{
    /* NOTE: To ensure safey, you must verify
             that file_ptr and buffer are not
             NULL prior to using this function.
    */
   
    // 1. Get a line from the file and store it in the buffer
    char *temp = fgets(buffer, 86, file_ptr);
    if (temp != NULL)
    {
        buffer[strlen(buffer) - 1] = '\0'; // Sets the newline character to a NULL character
    }

    return temp;
}

exit_code_t directory_exists(const char *directory_path)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    // 1. Check if the directory path is NULL
    if (NULL == directory_path)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // 2. Save the path
    DIR* directory = opendir(directory_path);

    // 3. Check if the directory exists
    if (NULL != directory)
    {
        closedir(directory);
        exit_code = E_DIRECTORY_EXISTS;
        goto END;
    }
    else if (ENOENT == errno)
    {
        exit_code = E_DIRECTORY_DOES_NOT_EXIST;
        goto END;
    }
    else
    {
        goto END; // Failed for some unknown reason
    }

END:
    return exit_code;
}

exit_code_t directory_empty(const char *directory_path)
{
    exit_code_t exit_code = E_DIRECTORY_EMPTY;

    // 1. Check if the directory path is NULL
    if (NULL == directory_path)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    DIR *dir = opendir(directory_path);
    if (NULL == dir)
    {
        exit_code = E_DIRECTORY_DOES_NOT_EXIST;
        goto END;
    }

    int num_contents = 0;

    // 2. Read the contents of the directory
    while (NULL != readdir(dir))
    {
        // Check if the contents include more than the current and parent directories
        if (++num_contents > 2)
        {
            exit_code = E_DIRECTORY_NOT_EMPTY;
            goto END;
        }
    }

    closedir(dir);

END:
    return exit_code;
}

exit_code_t create_directory(const char *directory_name)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == directory_name)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    // Attempt to create the directory with full read write and execute permissions
    if (mkdir(directory_name, 0777) == -1)
    {
        exit_code = E_MKDIR_FAILURE;
        print_exit_message(exit_code);
        goto END;
    }

    printf("[%s] directory created successfully\n", directory_name);

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_file(const char *file_name, const char *mode)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == file_name)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    FILE *file; // Create a file pointer

    // Attempt to create a file with the desired file name
    file = fopen(file_name, mode);
    if (NULL == file)
    {
        exit_code = E_FILE_CREATION_FAILURE;
        goto END;
    }

    fclose(file);
    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t write_to_text_file(const char *file_name, const char *text)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == file_name || NULL == text)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    FILE *file; // Create a file pointer

    // Attempt to open the file
    file = fopen(file_name, "w");
    if (NULL == file)
    {
        exit_code = E_FILE_NOT_WRITEABLE;
        goto END;
    }

    fprintf(file, text); // Write the text to the file

    exit_code = E_SUCCESS;
END:
    return exit_code;
}