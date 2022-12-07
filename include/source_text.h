#ifndef SOURCE_TEXT_H
#define SOURCE_TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "option_handler.h"
#include "string_functions.h"

/**
 * @brief Generates the contents of a .gitignore file for C
 * 
 * @return const char* 
 */
const char *generate_gitignore();

/**
 * @brief Generates Makefile content for C
 * 
 * @return const char* 
 */
char *generate_makefile(options_t *options);

/**
 * @brief Generates content for a custom exit_codes.c file
 * 
 * @return const char* 
 */
const char *generate_exit_codes_c();

/**
 * @brief Generates content for an exit_codes.h header file
 * 
 * @return const char* 
 */
const char *generate_exit_codes_h();

/**
 * @brief Generates content for a main.c file
 * 
 * @return const char* 
 */
const char *generate_main_c();

char *generate_custom_main_c(options_t *options, size_t idx);

/**
 * @brief Generates content for a main.h header file
 * 
 * @return const char* 
 */
const char *generate_main_h();

const char *generate_test_c();

char *generate_custom_test_c(options_t *options, size_t idx);

const char *generate_test_all_c();

const char *generate_custom_test_all_c(options_t *options);

#endif