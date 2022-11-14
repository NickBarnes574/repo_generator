#include "source_text.h"

const char *generate_gitignore()
{
    const char * gitignore =
    "\n\
    # Prerequisites\n\
    *.d\n\
    \n\
    # Object files\n\
    *.o\n\
    *.ko\n\
    *.obj\n\
    *.elf\n\
    \n\
    # Linker output\n\
    *.ilk\n\
    *.map\n\
    *.exp\n\
    \n\
    # Precompiled Headers\n\
    *.gch\n\
    *.pch\n\
    \n\
    # Libraries\n\
    *.lib\n\
    *.a\n\
    *.la\n\
    *.lo\n\
    \n\
    # Shared objects (inc. Windows DLLs)\n\
    *.dll\n\
    *.so\n\
    *.so.*\n\
    *.dylib\n\
    \n\
    # Executables\n\
    *.exe\n\
    *.out\n\
    *.app\n\
    *.i*86\n\
    *.x86_64\n\
    *.hex\n\
    \n\
    # Debug files\n\
    *.dSYM/\n\
    *.su\n\
    *.idb\n\
    *.pdb\n\
    \n\
    # Kernel Module Compile Results\n\
    *.mod*\n\
    *.cmd\n\
    .tmp_versions/\n\
    modules.order\n\
    Module.symvers\n\
    Mkfile.old\n\
    dkms.conf\n\
    ";

    return gitignore;
}

char *generate_makefile(char ** program_name, char **object_files, char **test_object_files)
{
    char *Makefile = "";

    strcpy(Makefile, 
    "# required options\n\
    CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla\n\
    VOPTS = --leak-check=full --show-leak-kinds=all --error-exitcode=1 -q\n\
    \n\
    # add header files to the compile path\n\
    CFLAGS += -I ./include/\n\
    \n\
    # all the the .o (object) files\n\
    OFILES = \\\n");

    // Adding the object files
    size_t idx = 0;
    while (object_files[idx] != NULL)
    {
        // Add the object files
        strcat(Makefile, (const char*)object_files[idx]);

        // Add a continuation
        if (NULL != object_files[idx + 1])
        {
            strcat(Makefile, "\\\n"); // Add "\" and a newline character
        }
        else
        {
            strcat(Makefile, "\n"); // Just add a newline character
        }
    }

    strcat(Makefile,
    "\n# all the the .o (object) files except the .o file that includes main(). Used for running unit tests.\n");

    // Adding the test object files
    idx = 0;
    while (object_files[idx] != NULL)
    {
        // Add the object files
        strcat(Makefile, (const char*)object_files[idx]);

        // Add a continuation
        if (NULL != object_files[idx + 1])
        {
            strcat(Makefile, "\\\n"); // Add "\" and a newline character
        }
        else
        {
            strcat(Makefile, "\n"); // Just add a newline character
        }
    }

    strcat(Makefile, "\n# the name of the output program\n");
    strcat(Makefile, "TARGET = ");
    strcat(Makefile, (const char*) program_name);
    strcat(Makefile, "\n");

    strcat(Makefile, "\n# individual tests");
    strcat(Makefile, (const char*)toupper(program_name));

    return Makefile;
}

const char *generate_exit_codes_c()
{
    const char *exit_codes_c =
    "\n\
    #include \"exit_codes.h\"\n\
    \n\
    // Citation:\n\
    // https://stackoverflow.com/questions/6286874/c-naming-suggestion-for-error-code-enums\n\
    \n\
    struct exit_message\n\
    {\n\
        int code;\n\
        const char *message;\n\
    }\n\
    \n\
    exit_message[] =\n\
    {\n\
        {E_SUCCESS, \"No errors.\\n\"},    // Success is first error\n\
        {E_DEFAULT_ERROR, \"Success state never achieved.\\n\"},\n\
    \n\
        // Other errors are listed by type\n\
    \n\
        //IO\n\
        {E_FILE_DOES_NOT_EXIST, \"File does not exist.\\n\"},\n\
        {E_FILE_NOT_READABLE, \"File cannot be read.\\n\"},\n\
        {E_FILE_NOT_WRITEABLE, \"File cannot be written to.\\n\"},\n\
        {E_FILE_CREATION_FAILURE, \"File cannot be created.\\n\"},\n\
        {E_DIRECTORY_DOES_NOT_EXIST, \"Directory does not exist.\\n\"},\n\
        {E_DIRECTORY_EXISTS, \"Directory exists.\\n\"},\n\
        {E_DIRECTORY_NOT_EMPTY, \"Directory is not empty.\\n\"},\n\
        {E_DIRECTORY_EMPTY, \"Directory is empty.\\n\"},\n\
        {E_MKDIR_FAILURE, \"Failed to create directory.\\n\"},\n\
        {E_INVALID_INPUT, \"Invalid input.\\n\"},\n\
        {E_OUT_OF_BOUNDS, \"Out of bounds.\\n\"},\n\
    \n\
        // Memory Management\n\
        {E_CMR_FAILURE, \"Calloc / malloc / realloc failure.\\n\"},\n\
        {E_NULL_POINTER, \"Unexpected NULL pointer detected.\\n\"},\n\
    \n\
        // General Data Structures\n\
        {E_CONTAINER_DOES_NOT_EXIST, \"Container does not exist.\\n\"},\n\
        {E_CONTAINER_EMPTY, \"Container empty when expected to be occupied.\\n\"},\n\
        {E_CONTAINER_NOT_EMPTY, \"Container occupied when expected to be empty.\\n\"},\n\
    \n\
        // Tree\n\
        {E_KEY_ALREADY_EXISTS, \"Key already exists in tree.\\n\"},\n\
        {E_KEY_NOT_FOUND, \"Search key not found in tree.\\n\"},\n\
    \n\
        // Linked List\n\
        {E_TOO_BIG, \"Position is greater than size of list.\\n\"},\n\
        {E_TOO_SMALL, \"Position is less than size of list.\\n\"},\n\
    };\n\
    \n\
    void print_exit_message(exit_code_t exit_code)\n\
    {\n\
        if (E_SUCCESS == exit_code)\n\
        {\n\
            return;\n\
        }\n\
    \n\
        if ((sizeof exit_message / sizeof exit_message[0]) > exit_code)\n\
        {\n\
            fprintf(stderr, \"%%s\", exit_message[exit_code].message);\n\
        }\n\
        else\n\
        {\n\
            fprintf(stderr, \"Unknown error detected.\\n\");\n\
        }\n\
    \n\
        return;\n\
    }\n\
    ";

    return exit_codes_c;
}

const char *generate_exit_codes_h()
{
    const char *exit_codes_h =
    "\n\
    #ifndef EXIT_CODES_H\n\
    #define EXIT_CODES_H\n\
    \n\
    #include <stdio.h>\n\
    #include <stdlib.h>\n\
    \n\
    // ENUM for custom error codes\n\
    typedef enum exit_code\n\
    {\n\
        E_SUCCESS,       // Success code (must be first code)\n\
        E_DEFAULT_ERROR, // Default error code (must be second code)\n\
    \n\
        // Other errors are listed by type\n\
    \n\
        // IO\n\
        E_FILE_DOES_NOT_EXIST,\n\
        E_FILE_NOT_READABLE,\n\
        E_FILE_NOT_WRITEABLE,\n\
        E_FILE_CREATION_FAILURE,\n\
        E_DIRECTORY_DOES_NOT_EXIST,\n\
        E_DIRECTORY_EXISTS,\n\
        E_DIRECTORY_NOT_EMPTY,\n\
        E_DIRECTORY_EMPTY,\n\
        E_MKDIR_FAILURE,\n\
        E_INVALID_INPUT,\n\
        E_OUT_OF_BOUNDS,\n\
    \n\
        // Memory Management\n\
        E_CMR_FAILURE,  // Calloc, Malloc, Realloc failure\n\
        E_NULL_POINTER, // Pointer is NULL\n\
    \n\
        // General Data Structures\n\
        E_CONTAINER_DOES_NOT_EXIST, // Container does not exist\n\
        E_CONTAINER_EMPTY,          // Container is empty\n\
        E_CONTAINER_NOT_EMPTY,      // Container is not empty\n\
    \n\
        // Tree\n\
        E_KEY_ALREADY_EXISTS, // Key already exists\n\
        E_KEY_NOT_FOUND,      // Search key not found\n\
    \n\
        // Linked List\n\
        E_TOO_SMALL, // Position is less than size of list\n\
        E_TOO_BIG,   // Position is greater than size of list\n\
    \n\
    } exit_code_t;\n\
    \n\
    // struct using custom err_codes_t to print related error messages\n\
    typedef struct exit_message exit_message_t;\n\
    \n\
    /**\n\
     * @brief function to print custom exit messages.\n\
     *\n\
    * @param exit_code exit code by which to find the message string.\n\
    */\n\
    void print_exit_message(exit_code_t exit_code);\n\
    \n\
    #endif\n\
    \n\
    ";

    return exit_codes_h;
}

const char *generate_main_c()
{
    const char *main_c =
    "\n\
    #include \"main.h\"\n\
    \n\
    int main(int argc, char **argv)\n\
    {\n\
        exit_code_t exit_code = E_DEFAULT_ERROR;\n\
    \n\
    END:\n\
        return exit_code;\n\
    }\n\
    ";

    return main_c;
}

const char *generate_main_h()
{
    const char *main_h =
    "\n\
    #ifndef MAIN_H\n\
    #define MAIN_H\n\
    \n\
    #include <stdio.h>\n\
    #include <stdlib.h>\n\
    \n\
    #include \"exit_codes.h\" // for exit codes\n\
    \n\
    #endif\n\
    ";

    return main_h;
}