#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // access()
#include <string.h> // strlen() fgets() fgetc()
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h> // mkdir()

#include "exit_codes.h"

/**
 * @brief Checks if a filename exists
 * 
 * @param filename the filename to be passed
 * @return exit_code_t 
 */
exit_code_t file_exists(const char *filename);

/**
 * @brief Checks if a filename is readable
 * 
 * @param filename the filename to be passed
 * @return exit_code_t 
 */
exit_code_t file_readable(const char *filename);

/**
 * @brief Checks if a line can be read from a file
 * 
 * @param file_ptr the file pointer to be passed
 * @param buffer the buffer to be passed
 * @return exit_code_t
 */
exit_code_t line_readable(FILE *file_ptr, char *buffer);

/**
 * @brief Validates a filename to check if it can be opened
 * 
 * @param filename the filename to be passed
 * @return exit_code_t 
 */
exit_code_t validate_file(const char *filename);

/**
 * @brief Checks if a directory exists
 * 
 * @param directory the directory to be passed
 * @return exit_code_t 
 */
exit_code_t directory_exists(const char *directory_path);

/**
 * @brief Checks if a directory is empty
 * 
 * @param directory_path the directory to be passed
 * @return exit_code_t 
 */
exit_code_t directory_empty(const char *directory_path);

/**
 * @brief Create a directory
 * 
 * @param directory_name the name of the directory
 * @return exit_code_t 
 */
exit_code_t create_directory(const char *directory_name);

/**
 * @brief Create a file
 * 
 * @param file_name the name of the file to create
 * @param mode the mode in which to open the file
 * @return exit_code_t 
 */
exit_code_t create_file(const char *file_name, char mode);

/**
 * @brief Writes text to a text file
 * 
 * @param file_name the name of the file to write to
 * @param text the text to write
 * @return exit_code_t 
 */
exit_code_t write_to_text_file(const char *file_name, const char *text);

/**
 * @brief Reads a line from a file
 * 
 * @param file_ptr the file pointer to be passed
 * @param buffer the buffer to be passed
 * @return char* 
 */
char *read_line(FILE *file_ptr, char *buffer);

#endif
