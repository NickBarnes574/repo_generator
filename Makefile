# required options
CFLAGS += -Wall -Wextra -Wpedantic -Waggregate-return -Wwrite-strings -Wfloat-equal -Wvla
VOPTS = --leak-check=full --show-leak-kinds=all --error-exitcode=1 -q

# add header files to the compile path
CFLAGS += -I ./include/

# all the the .o (object) files
OFILES = \
src/exit_codes.o \
src/main.o\
src/file_io.o \
src/initializer.o \
src/option_handler.o \
src/signal_handler.o \
src/source_text.o \
src/user_input.o \
src/printer.o

# all the the .o (object) files except the .o file that includes main(). Used for running unit tests.
TEST_OFILES = \
src/exit_codes.o \
src/file_io.o \
src/initializer.o \
src/option_handler.o \
src/signal_handler.o \
src/source_text.o \
src/user_input.o \
src/printer.o

# the name of the output program
TARGET = initialize_repo

# individual tests
INITIALIZE_REPO_TESTS = test/initialize_repo_tests.o

# combine all the tests into one list
ALL_TESTS = test/initialize_repo_test_all.o $(INITIALIZE_REPO_TESTS)

# make everything
.PHONY: all
all: $(OFILES) $(TARGET)

# makes the program
.PHONY: initialize_repo
initialize_repo: $(OFILES)
		$(CC) $(CFLAGS) $(OFILES) -o $(TARGET)

# makes a profile
.PHONY: profile
profile: clean
profile: CFLAGS += -pg
profile: initialize_repo

# makes a debug version of the program for use with valgrind
.PHONY: debug
debug: CFLAGS += -g -gstabs -O0
debug: initialize_repo

# delete the library and all the .o files
.PHONY: clean
clean:
	$(RM) $(TARGET)
	find . -type f -name "*.o" -exec rm -f {} \;
	find . -type f -perm /111 -exec rm -f {} \;

# creates and runs tests using valgrind
.PHONY: valcheck
valcheck: CFLAGS += -g
valcheck: test/initialize_repo_tests
# disable forking in order to run tests with valgrind
	CK_FORK=no valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=yes ./$^

# creates and runs tests
.PHONY: check
check: CFLAGS += -g
check: test/initialize_repo_tests
	./$^

# Comprehensive test testing all dependencies
test/initialize_repo_tests: CHECKLIBS = -lcheck -lm -lrt -lpthread -lsubunit
test/initialize_repo_tests: $(ALL_TESTS) $(TEST_OFILES)
	$(CC) $(CFLAGS) $(ALL_TESTS) $(TEST_OFILES) $(CHECKLIBS) -o test/initialize_repo_tests
