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
    //DEBUG
    printf("NUM_NAMES = [%ld]\n", num_names);
    //DEBUG

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
            *Makefile += snprintf(*Makefile, max_len, "TARGET_%ld = %s\n", idx+1, prog_names[idx]);
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

    // Generate a default MAIN_OBJ file
    if (num_names == 0)
    {
        *Makefile += snprintf(*Makefile, max_len, "MAIN_OBJ = src/main.o\n");
    }

    // Generate custom program name(s) passed in from the command line
    else
    {
        for (size_t idx = 0; idx < num_names; idx++)
        {
            *Makefile += snprintf(*Makefile, max_len, "TARGET_%ld_MAIN = src/%s/main.o\n", idx+1, prog_names[idx]);
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
            "%s_TESTS = \n", temp);
            free(temp);
        }
    }

    // Generate default tests
    else
    {
        *Makefile += snprintf(*Makefile, max_len,
        "PROJECT_TESTS = \n");
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

    char **prog_names = options->prog_names;
    size_t num_names = options->num_prog_names;

    if (NULL == Makefile || NULL == options)
    {
        exit_code = E_NULL_POINTER;
        goto END;
    }

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

// static exit_code_t default_func(char **Makefile, options_t *options, size_t max_len)
// {
//     exit_code_t exit_code = E_DEFAULT_ERROR;

//     if (NULL == Makefile || NULL == options)
//     {
//         exit_code = E_NULL_POINTER;
//         goto END;
//     }

//     exit_code = E_SUCCESS;
// END:
//     return exit_code;
// }

char *generate_makefile(options_t *options)
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    size_t num_names = options->num_prog_names;
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
Makefile += snprintf(Makefile, max_len,
"# make everything\n\
.PHONY: all\n\
all: $(MAIN_OBJ_FILE) $(OBJ_FILES) ");

// Set only 1 target if a program name is not passed in
if (num_names == 0)
{
    Makefile += snprintf(Makefile, max_len,
    "$(TARGET)\n");
}

// Set the number of targets that were passed in
else
{
    for (size_t idx = 0; idx < num_names - 1; idx++)
    {
        Makefile += snprintf(Makefile, max_len, "$(TARGET_%ld)", idx+1);

        // Add a space between targets unless it's the last target
        if ((idx + 1) < (num_names - 1))
        {
            Makefile += snprintf(Makefile, max_len, " ");
        }
    }
}
Makefile += snprintf(Makefile, max_len,
"\n\n");

// Make the target(s)
Makefile += snprintf(Makefile, max_len,
"# makes the program\n\
.PHONY: $(TARGET)\n\
initialize_repo: $(MAIN_OBJ_FILE) $(OBJ_FILES)\n\
        $(CC) $(CFLAGS) $(MAIN_OBJ_FILE) $(OBJ_FILES) -o $(TARGET)\n\n");

// Make debug
Makefile += snprintf(Makefile, max_len,
"# makes a debug version of the program for use with valgrind\n\
.PHONY: debug\n\
debug: CFLAGS += -g -gstabs -O0\n\
debug: $(TARGET)\n\n");

// Make profile
Makefile += snprintf(Makefile, max_len,
"# makes a profile\n\
.PHONY: profile\n\
profile: clean\n\
profile: CFLAGS += -pg\n\
profile: $(TARGET)\n\n");

// Make clean
Makefile += snprintf(Makefile, max_len,
"# delete the program and all the .o files\n\
.PHONY: clean\n\
clean:\n\
    $(RM) $(TARGET)\n\
    find . -type f -name \"*.o\" -exec rm -f {} \\;\n\
    find . -type f -perm /111 -exec rm -f {} \\;\n\n");

// Create and run tests using valgrind
Makefile += snprintf(Makefile, max_len,
"# creates and runs tests using valgrind\n\
.PHONY: valcheck\n\
valcheck: CFLAGS += -g\n\
valcheck: test/initialize_repo_tests\n\
# disable forking in order to run tests with valgrind\n\
    CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$^\n\n");

// Create and run tests normally
Makefile += snprintf(Makefile, max_len,
"# creates and runs tests\n\
.PHONY: check\n\
check: CFLAGS += -g\n\
check: test/initialize_repo_tests\n\
    ./$^\n\n");

// Inititialize tests with libcheck
Makefile += snprintf(Makefile, max_len,
"# Comprehensive test testing all dependencies\n\
test/initialize_repo_tests: CHECKLIBS = -lcheck -lm -lrt -lpthread -lsubunit\n\
test/initialize_repo_tests: $(ALL_TESTS) $(OBJ_FILES)\n\
    $(CC) $(CFLAGS) $(ALL_TESTS) $(OBJ_FILES) $(CHECKLIBS) -o test/initialize_repo_tests\n");

END:
    return strdup(buffer);
}

const char *generate_makefile_multi_program()
{
    static const char *Makefile =

"# required options\n\
CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla\n\
\n\
# add header files to the compile path\n\
CFLAGS += -I ./include/\n\
\n\
# the object file which contains main\n\
MAIN_OBJ_FILE = src/main.o\n\
\n\
# all of the other object files outside of main\n\
OBJ_FILES = \\\n\
src/exit_codes.o \n\
\n\
# the name of the output program\n\
TARGET = #PROGRAM_NAME\n\
\n\
# individual tests\n\
TEST_OBJ_FILES = #test/example_tests.o\n\
\n\
# combine all the tests into one list\n\
ALL_TESTS = test/initialize_repo_test_all.o $(TEST_OBJ_FILES)\n\
\n\
# make everything\n\
.PHONY: all\n\
all: $(MAIN_OBJ_FILE) $(OBJ_FILES) $(TARGET)\n\
\n\
# makes the program\n\
.PHONY: $(TARGET)\n\
initialize_repo: $(MAIN_OBJ_FILE) $(OBJ_FILES)\n\
        $(CC) $(CFLAGS) $(MAIN_OBJ_FILE) $(OBJ_FILES) -o $(TARGET)\n\
\n\
# makes a debug version of the program for use with valgrind\n\
.PHONY: debug\n\
debug: CFLAGS += -g -gstabs -O0\n\
debug: $(TARGET)\n\
\n\
# makes a profile\n\
.PHONY: profile\n\
profile: clean\n\
profile: CFLAGS += -pg\n\
profile: $(TARGET)\n\
\n\
# delete the program and all the .o files\n\
.PHONY: clean\n\
clean:\n\
    $(RM) $(TARGET)\n\
    find . -type f -name \"*.o\" -exec rm -f {} \\;\n\
    find . -type f -perm /111 -exec rm -f {} \\;\n\
\n\
# creates and runs tests using valgrind\n\
.PHONY: valcheck\n\
valcheck: CFLAGS += -g\n\
valcheck: test/initialize_repo_tests\n\
# disable forking in order to run tests with valgrind\n\
    CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$^\n\
\n\
# creates and runs tests\n\
.PHONY: check\n\
check: CFLAGS += -g\n\
check: test/initialize_repo_tests\n\
    ./$^\n\
\n\
# Comprehensive test testing all dependencies\n\
test/initialize_repo_tests: CHECKLIBS = -lcheck -lm -lrt -lpthread -lsubunit\n\
test/initialize_repo_tests: $(ALL_TESTS) $(OBJ_FILES)\n\
    $(CC) $(CFLAGS) $(ALL_TESTS) $(OBJ_FILES) $(CHECKLIBS) -o test/initialize_repo_tests\n\
";

    return Makefile;
}

const char *generate_exit_codes_c()
{
    static const char *exit_codes_c =
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
    static const char *exit_codes_h =
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
    static const char *main_c =
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
    static const char *main_h =
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

const char *generate_test_c()
{
    static const char *tests_c =
"\n\
#include <check.h>\n\
#include <stdio.h>\n\
#include <stdlib.h>\n\
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
    return trie_test_suite;\n\
}\n\
";

    return tests_c;
}

const char *generate_test_all_c()
{
    const char *test_all_c =
"\n\
#include <check.h>\n\
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