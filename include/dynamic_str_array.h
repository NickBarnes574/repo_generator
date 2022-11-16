#ifndef DYNAMIC_STR_ARRAY
#define DYNAMIC_STR_ARRAY

#ifndef WORD_LIST_H
#define WORD_LIST_H

#include <stdio.h> // printf
#include <string.h> // strdup
#include <stdbool.h> // for bool
#include <stdlib.h> // for size_t

#include "exit_codes.h"

/**
 * @brief Typedef for a str_arr_ struct
 * 
 */
typedef struct str_arr_ str_arr_t;

/**
 * @brief Create a dynamic string array object
 * 
 * @param initial_size 
 * @return str_arr_t* 
 */
str_arr_t *dystr_create(size_t initial_size);

/**
 * @brief Destroy a dynamic string array object
 * 
 * @param dyn_str_arr the struct to be passed
 */
void dystr_destroy(str_arr_t *dyn_str_arr);

/**
 * @brief Insert a char* (string) into the dynamic array
 * 
 * @param dyn_str_arr the struct to be passed 
 * @param str the string to be added to the dynamic array
 * @return true 
 * @return false 
 */
exit_code_t dystr_insert_element(str_arr_t *dyn_str_arr, const char *str);

/**
 * @brief Reallocate space for the dynamic array when capacity reaches limit
 * 
 * @param dyn_str_arr the array struct to be passed
 * @return exit_code_t 
 */
exit_code_t dystr_realloc(str_arr_t *const dyn_str_arr);

/**
 * @brief Get the value at the specified index
 * 
 * @param dyn_str_arr the struct to be passed
 * @param index the index to be checked
 * @return char* 
 */
char *dystr_get_element(str_arr_t *const dyn_str_arr, size_t index);

/**
 * @brief Get the list of strings
 * 
 * @param dyn_str_arr the struct to be passed
 * @return char** 
 */
char **dystr_get_list(str_arr_t *const dyn_str_arr);

/**
 * @brief Set the value at the specified index with a new value
 * 
 * @param dyn_str_arr the struct to be passed
 * @param index the index to be changed
 * @param str the value to be set
 */
exit_code_t dystr_set_element(str_arr_t *const dyn_str_arr, size_t index, const char *str);

/**
 * @brief Get the number of elements in the array
 * 
 * @param dyn_str_arr the struct to be passed
 * @return int 
 */
int dystr_get_size(str_arr_t *const dyn_str_arr);

/**
 * @brief Get the total capacity of the array
 * 
 * @param dyn_str_arr the struct to be passed
 * @return int 
 */
int dystr_get_total_capacity(str_arr_t *const dyn_str_arr);

#endif


#endif