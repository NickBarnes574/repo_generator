#include "source_text.h"

const char *generate_gitignore()
{
    static const char * gitignore =
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
\n\
# Template folder\n\
templates/\n\
";

    return gitignore;
}
static exit_code_t generate_program_names(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# the name of the output program(s)\n");

    // Generate a default program name 'program'
    if (num_names == 0)
    {
        *Makefile += snprintf(*Makefile, max_len, "TARGET = program\n");
    }

    // Generate custom program name(s) passed in from the command line
    else
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len, "%s = %s\n", temp, prog_names[idx]);
            free(temp);
        }
    }
    *Makefile += snprintf(*Makefile, max_len,
    "\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t generate_main_object_files(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# the object file(s) that contains main()\n");

    // Generate a default main object file
    if (num_names == 0)
    {
        *Makefile += snprintf(*Makefile, max_len, "TARGET_MAIN = src/main.o\n");
    }

    // Generate custom program name(s) passed in from the command line
    else
    {
        if (num_names >= 2)
        {
            for (size_t idx = 0; idx < num_names; idx++)
            {
                // Convert program names to upper case
                char *temp = str_toupper(prog_names[idx]);

                *Makefile += snprintf(*Makefile, max_len, "%s_MAIN = src/%s/main.o\n", temp, prog_names[idx]);
                free(temp);
            }
        }
        else
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[0]);

            *Makefile += snprintf(*Makefile, max_len, "%s_MAIN = src/main.o\n", temp);
            free(temp);
        }
    }
    *Makefile += snprintf(*Makefile, max_len,
    "\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t generate_other_object_files(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    // Generate object files specific to each program
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            *Makefile += snprintf(*Makefile, max_len,
            "# object files specific to %s\n", prog_names[idx]);

            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "%s_OBJ = \\\n\n", temp);
            free(temp);
        }
    }

    // Generate common object files
    *Makefile += snprintf(*Makefile, max_len,
    "# common object files\n");
    *Makefile += snprintf(*Makefile, max_len,
    "COMMON_OBJ = \\\n\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t generate_test_files(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# individual test files\n");

    // Generate tests for each program
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "%s_TESTS = ", temp);

            if (num_names >= 2)
            {
                *Makefile += snprintf(*Makefile, max_len,
                "test/%s_tests.o\n", options->prog_names[idx]);
            }

            else
            {
                *Makefile += snprintf(*Makefile, max_len,
                "test/tests.o\n");
            }

            free(temp);
        }
    }
    
    // Generate default tests
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "PROJECT_TESTS = ");

        *Makefile += snprintf(*Makefile, max_len,
        "test/tests.o\n");
    }

    *Makefile += snprintf(*Makefile, max_len,
    "\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t generate_combine_tests(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# combine all the tests into one list\n");

    *Makefile += snprintf(*Makefile, max_len,
    "ALL_TESTS = test/project_test_all.o ");

    // Generate a combined list of tests by adding tests for each program
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s_TESTS)", temp);
            free(temp);

            // Add a space between tests unless it's the last test
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }
        }
    }

    // Generate the default list of tests
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "$(PROJECT_TESTS)");
    }

    *Makefile += snprintf(*Makefile, max_len,
    "\n\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t make_all(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# make everything\n.PHONY: all\nall: ");

    // Gather all the programs to make
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s)", temp);
            free(temp);

            // Add a space between tests unless it's the last test
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }
        }
    }

    // Get the default program to make
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "$(TARGET)");
    }

    *Makefile += snprintf(*Makefile, max_len,
    "\n\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t make_targets(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }
    
    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    // Generate the targets
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            // Add the depedencies for the target program
            *Makefile += snprintf(*Makefile, max_len,
            "# makes the %s program\n.PHONY: $(%s)\n%s: $(%s_MAIN) $(%s_OBJ) $(COMMON_OBJ)\n",
            prog_names[idx], temp, prog_names[idx], temp, temp);

            // Add the compiler flags
            *Makefile += snprintf(*Makefile, max_len,
            "\t$(CC) $(CFLAGS) $(%s_MAIN) $(%s_OBJ) $(COMMON_OBJ) -o $(%s)\n\n", temp, temp, temp);

            free(temp);
        }
    }

    // Make the default target
    else
    {
        // Add the depedencies for the target program
        *Makefile += snprintf(*Makefile, max_len,
        "# makes the target program\n.PHONY: $(TARGET)\nprogram: $(TARGET_MAIN) $(COMMON_OBJ)\n");

        // Add the compiler flags
        *Makefile += snprintf(*Makefile, max_len,
        "\t$(CC) $(CFLAGS) $(TARGET_MAIN) $(COMMON_OBJ) -o $(TARGET)\n\n");
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t make_debug(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# makes a debug version of the program(s) for use with valgrind\n");

    *Makefile += snprintf(*Makefile, max_len,
    ".PHONY: debug\ndebug: CFLAGS += -g\ndebug: ");

    // Make debug versions of each program
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s)", temp);

            // Add a space between targets unless it's the last target
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }

            free(temp);
        }
    }

    // Make the default debug progam
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "$(TARGET)");
    }

    *Makefile += snprintf(*Makefile, max_len,
    "\n\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t make_profile(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# makes a profile\n");

    *Makefile += snprintf(*Makefile, max_len,
    ".PHONY: profile\nprofile: clean\nprofile: CFLAGS += -pg\nprofile: ");

    // Make profiles of each program
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s)", temp);

            // Add a space between targets unless it's the last target
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }

            free(temp);
        }
    }

    // Make the default debug profile
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "$(TARGET)");
    }

    *Makefile += snprintf(*Makefile, max_len,
    "\n\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t make_clean(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# delete the program(s) and all the .o files\n");

    *Makefile += snprintf(*Makefile, max_len,
    ".PHONY: clean\nclean:\n\t$(RM) ");

    // Remove each program
    if (num_names > 0)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s)", temp);

            // Add a space between targets unless it's the last target
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }

            free(temp);
        }
    }

    // Remove the default target
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "$(TARGET)");
    }

    *Makefile += snprintf(*Makefile, max_len,
    "\n\tfind . -type f -name \"*.o\" -exec rm -f {} \\;");

    *Makefile += snprintf(*Makefile, max_len,
    "\n\n");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

static exit_code_t run_tests(char **Makefile, options_t *options, size_t max_len)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    *Makefile += snprintf(*Makefile, max_len,
    "# Comprehensive test testing all dependencies\n");

    *Makefile += snprintf(*Makefile, max_len,
    "test/project_tests: CHECKLIBS = -lcheck -lm -lrt -lpthread -lsubunit\n");

    *Makefile += snprintf(*Makefile, max_len,
    "test/project_tests: $(ALL_TESTS) ");

    // Add all the target programs
    if (num_names >= 2)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s_OBJ)", temp);

            // Add a space between targets unless it's the last target
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }

            free(temp);
        }
    }

    *Makefile += snprintf(*Makefile, max_len,
    " $(COMMON_OBJ)\n");

    *Makefile += snprintf(*Makefile, max_len,
    "\t$(CC) $(CFLAGS) $(ALL_TESTS) ");

    if (num_names >= 2)
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            // Convert program names to upper case
            char *temp = str_toupper(prog_names[idx]);

            *Makefile += snprintf(*Makefile, max_len,
            "$(%s_OBJ)", temp);

            // Add a space between targets unless it's the last target
            if ((idx + 1) < (num_names))
            {
                *Makefile += snprintf(*Makefile, max_len, " ");
            }

            free(temp);
        }
    }

    *Makefile += snprintf(*Makefile, max_len,
    " $(COMMON_OBJ) $(CHECKLIBS) -o test/project_tests");

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

char *generate_makefile(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    size_t max_len = 5000;
    static char buffer[5000];
    char *Makefile = buffer;

// Required Options
Makefile += snprintf(Makefile, max_len,
"# required options\n\
CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla\n\n");

// Header Files
Makefile += snprintf(Makefile, max_len,
"# add header files to the compile path\n\
CFLAGS += -I ./include/\n\n");

// Generate program name(s)
exit_code = generate_program_names(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Main object files
exit_code = generate_main_object_files(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// All other object files
exit_code = generate_other_object_files(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Individual tests
exit_code = generate_test_files(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Test list
exit_code = generate_combine_tests(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Make all
exit_code = make_all(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Make the target(s)
exit_code = make_targets(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Make debug
exit_code = make_debug(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Make profile
exit_code = make_profile(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Make clean
exit_code = make_clean(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

// Create and run tests using valgrind
Makefile += snprintf(Makefile, max_len,
"# creates and runs tests using valgrind\n\
.PHONY: valcheck\n\
valcheck: CFLAGS += -g\n\
valcheck: test/project_tests\n\
# disable forking in order to run tests with valgrind\n\
\tCK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$^\n\n");

// Create and run tests normally
Makefile += snprintf(Makefile, max_len,
"# creates and runs tests\n\
.PHONY: check\n\
check: CFLAGS += -g\n\
check: test/project_tests\n\
\t./$^\n\n");

// Run tests
exit_code = run_tests(&Makefile, options, max_len);
if (E_SUCCESS != exit_code)
{
    Makefile = NULL;
    goto END;
}

END:
    return strdup(buffer);
}

const char *generate_exit_codes_c()
{
    static const char *exit_codes_c =
"#include \"exit_codes.h\"\n\
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
    static const char *exit_codes_h =
"#ifndef EXIT_CODES_H\n\
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

char *generate_custom_main_c(options_t *options, size_t idx)
{
    if (NULL == options)
    {
        return NULL;
    }

    size_t max_len = 5000;
    static char buffer[5000];
    char *main = buffer;

    char **prog_names = options->prog_names;

    main += snprintf(main, max_len,
    "#include \"%s/main.h\"\n\n", prog_names[idx]);

    main += snprintf(main, max_len,
    "int main(int argc, char **argv)\n{\n");

    main += snprintf(main, max_len,
    "\texit_code_t exit_code = E_DEFAULT_ERROR;\n\nEND:\n");

    main += snprintf(main, max_len,
    "\treturn exit_code;\n}");

    return strdup(buffer);
}

const char *generate_main_c()
{
    static const char *main_c =
"#include \"main.h\"\n\
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
    static const char *main_h =
"#ifndef MAIN_H\n\
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

const char *generate_test_c()
{
    static const char *tests_c =
"#include <check.h>\n\
#include <stdio.h>\n\
#include <stdlib.h>\n\
\n\
#include \"exit_codes.h\"\n\
\n\
// // TEST CASE\n\
// //***********************************************************************************************\n\
// // XXXX TESTS\n\
// START_TEST(test_YYYY)\n\
// {\n\
\n\
// }\n\
// END_TEST\n\
\n\
// // TEST LIST\n\
// static TFun XXXX_tests[] =\n\
// {\n\
//     test_YYYY,\n\
//     NULL\n\
// };\n\
\n\
static void add_tests(TCase * test_cases, TFun * test_functions)\n\
{\n\
    while (* test_functions)\n\
    {\n\
        // add the test from the core_tests array to the tcase\n\
        tcase_add_test(test_cases, * test_functions);\n\
        test_functions++;\n\
    }\n\
}\n\
\n\
Suite *project_test_suite(void)\n\
{\n\
    Suite *project_test_suite = suite_create(\"Project Tests\");\n\
\n\
    // CREATE TESTS\n\
\n\
    // //Create XXXX tests\n\
    // TFun *XXXX_test_list = XXXX_tests;\n\
    // TCase *XXXX_test_cases = tcase_create(\" XXXX() Tests\");\n\
    // add_tests(XXXX_test_cases, XXXX_test_list);\n\
    // suite_add_tcase(project_test_suite, XXXX_test_cases);\n\
\n\
    return project_test_suite;\n\
}\n\
";

    return tests_c;
}

char *generate_custom_test_c(options_t *options, size_t idx)
{
    if (NULL == options)
    {
        return NULL;
    }

    size_t max_len = 5000;
    static char buffer[5000];
    char *main = buffer;

    char **prog_names = options->prog_names;
    
    main += snprintf(main, max_len,
    "#include <check.h>\n\
#include <stdio.h>\n\
#include <stdlib.h>\n\
\n\
#include \"exit_codes.h\"\n\
\n\
// // TEST CASE\n\
// //***********************************************************************************************\n\
// // XXXX TESTS\n\
// START_TEST(test_YYYY)\n\
// {\n\
\n\
// }\n\
// END_TEST\n\
\n\
// // TEST LIST\n\
// static TFun XXXX_tests[] =\n\
// {\n\
//     test_YYYY,\n\
//     NULL\n\
// };\n\
\n\
static void add_tests(TCase * test_cases, TFun * test_functions)\n\
{\n\
    while (* test_functions)\n\
    {\n\
        // add the test from the core_tests array to the tcase\n\
        tcase_add_test(test_cases, * test_functions);\n\
        test_functions++;\n\
    }\n\
}\n\
\n");
    
    main += snprintf(main, max_len,
    "Suite *%s_test_suite(void)\n", prog_names[idx]);

    main += snprintf(main, max_len,
    "{\n\tSuite *%s_test_suite = suite_create(\"%s tests\");\n", prog_names[idx], prog_names[idx]);

    main += snprintf(main, max_len,
    "\n\
    // CREATE TESTS\n\
\n\
    // //Create XXXX tests\n\
    // TFun *XXXX_test_list = XXXX_tests;\n\
    // TCase *XXXX_test_cases = tcase_create(\" XXXX() Tests\");\n\
    // add_tests(XXXX_test_cases, XXXX_test_list);\n");

    main += snprintf(main, max_len,
    "    // suite_add_tcase(%s_test_suite, XXXX_test_cases);\n\
\n\
    return %s_test_suite;\n\
}", prog_names[idx], prog_names[idx]);

    return strdup(buffer);
}

const char *generate_test_all_c()
{
    const char *test_all_c =
"#include <check.h>\n\
\n\
extern Suite *project_test_suite(void);\n\
\n\
int main(int argc, char** argv)\n\
{\n\
  // Suppress unused parameter warnings\n\
  (void) argv[argc];\n\
\n\
  // create test suite runner\n\
  SRunner *sr = srunner_create(NULL);\n\
\n\
  // prepare the test suites\n\
  srunner_add_suite(sr, project_test_suite());\n\
\n\
  // run the test suites\n\
  srunner_run_all(sr, CK_VERBOSE);\n\
\n\
  // report the test failed status\n\
  int tests_failed = srunner_ntests_failed(sr);\n\
  srunner_free(sr);\n\
\n\
  // return 1 or 0 based on whether or not tests failed\n\
  return (tests_failed == 0) ? 0 : 1;\n\
}\n\
";

    return test_all_c;
}

const char *generate_custom_test_all_c(options_t *options)
{
    if (NULL == options)
    {
        return NULL;
    }

    size_t max_len = 5000;
    static char buffer[5000];
    char *main = buffer;

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;
    
    main += snprintf(main, max_len,
"#include <check.h>\n\
\n");

for (size_t idx = 0; idx < num_names; idx++)
{
    main += snprintf(main, max_len,
    "extern Suite *%s_test_suite(void);\n", prog_names[idx]);
}

    main += snprintf(main, max_len,
"\nint main(int argc, char** argv)\n\
{\n\
  // Suppress unused parameter warnings\n\
  (void) argv[argc];\n\
\n\
  // create test suite runner\n\
  SRunner *sr = srunner_create(NULL);\n\
\n\
  // prepare the test suites\n");

for (size_t idx = 0; idx < num_names; idx++)
{
    main += snprintf(main, max_len,
"  srunner_add_suite(sr, %s_test_suite());\n", prog_names[idx]);
}

    main += snprintf(main, max_len,
"\n  // run the test suites\n\
  srunner_run_all(sr, CK_VERBOSE);\n\
\n\
  // report the test failed status\n\
  int tests_failed = srunner_ntests_failed(sr);\n\
  srunner_free(sr);\n\
\n\
  // return 1 or 0 based on whether or not tests failed\n\
  return (tests_failed == 0) ? 0 : 1;\n\
}\n\
");

    return strdup(buffer);
}