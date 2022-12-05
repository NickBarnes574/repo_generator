CC = gcc

# required options
CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla

# add header files to the compile path
CFLAGS += -I ./include/

# the object file which contains main
MAIN_OBJ_FILE = src/main.o

# all of the other object files outside of main
OBJ_FILES = \
src/exit_codes.o \
src/file_io.o \
src/initializer.o \
src/src_paths.o \
src/dest_paths.o \
src/option_handler.o \
src/signal_handler.o \
src/source_text.o \
src/user_input.o \
src/printer.o

# the name of the output program
TARGET = pk

# individual tests
TEST_OBJ_FILES = test/pk_tests.o

# combine all the tests into one list
ALL_TESTS = test/pk_test_all.o $(TEST_OBJ_FILES)

# make everything
.PHONY: all
all: $(MAIN_OBJ_FILE) $(OBJ_FILES) $(TARGET)

# makes the program
.PHONY: $(TARGET)
pk: $(MAIN_OBJ_FILE) $(OBJ_FILES)
		$(CC) $(CFLAGS) $(MAIN_OBJ_FILE) $(OBJ_FILES) -o $(TARGET)

# makes a debug version of the program for use with valgrind
.PHONY: debug
debug: CFLAGS += -g -gstabs -O0
debug: $(TARGET)

# makes a profile
.PHONY: profile
profile: clean
profile: CFLAGS += -pg
profile: $(TARGET)

# delete the program and all the .o files
.PHONY: clean
clean:
	$(RM) $(TARGET)
	find . -type f -name "*.o" -exec rm -f {} \;
	find . -type f -perm /111 -exec rm -f {} \;

# creates and runs tests using valgrind
.PHONY: valcheck
valcheck: CFLAGS += -g
valcheck: test/pk_tests
# disable forking in order to run tests with valgrind
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$^

# creates and runs tests
.PHONY: check
check: CFLAGS += -g
check: test/pk_tests
	./$^

# Comprehensive test testing all dependencies
test/pk_tests: CHECKLIBS = -lcheck -lm -lrt -lpthread -lsubunit
test/pk_tests: $(ALL_TESTS) $(OBJ_FILES)
	$(CC) $(CFLAGS) $(ALL_TESTS) $(OBJ_FILES) $(CHECKLIBS) -o test/generate_repo_tests
