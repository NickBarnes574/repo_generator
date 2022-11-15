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
    \n\
    # Template folder\n\
    templates/\n\
    ";

    return gitignore;
}

const char *generate_makefile_single_program()
{
    const char *Makefile =

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

const char *generate_makefile_multi_program()
{
    const char *Makefile =

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