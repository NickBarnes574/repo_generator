#ifndef SOURCE_TEXT_H
#define SOURCE_TEXT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
const char *generate_makefile_single_program();

const char *generate_makefile_multi_program();

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

/**
 * @brief Generates content for a main.h header file
 * 
 * @return const char* 
 */
const char *generate_main_h();

#endif