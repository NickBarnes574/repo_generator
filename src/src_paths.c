#include "src_paths.h"

void free_src_paths(char **src_paths)
{
    for (size_t idx = 0; idx < NUMBER_OF_CODES; idx++)
    {
        free(src_paths[idx]);
        src_paths[idx] = NULL;
    }
}

void destroy_src_paths(char **src_paths)
{
    // Destroy each path individually
    free_src_paths(src_paths);

    // Destroy the array itself
    free(src_paths);
    src_paths = NULL;
}

char **generate_src_paths()
{    
    // Get the user's home directory
    const char *home = (const char*)getenv("HOME");

    src_codes_t src_codes;

    // Allocate space for the path array
    char **src_paths = calloc(1, sizeof(char**));
    if (NULL == src_paths)
    {
        free (src_paths);
        src_paths = NULL;
        goto END;
    }

    // Allocate space for each path
    for (size_t idx = 0; idx < src_codes; idx++)
    {
        src_paths[idx] = calloc(1, sizeof(char*));
        if (NULL == src_paths[idx])
        {
            destroy_src_paths(src_paths);
            goto END;
        }
    }

    /********************************************************
     * REPO_GENERATOR
     * user/home/repo_generator
    *********************************************************/
    src_paths[DIR_REPO] = append_path(home, "repo_generator");
    const char *repo = src_paths[DIR_REPO];

    /********************************************************
     * SAVE_DATA
     * user/home/repo_generator/save_data
    *********************************************************/
    src_paths[DIR_SAVE_DATA] = append_path(repo, "save_data");
    const char *save_data = src_paths[DIR_SAVE_DATA];

    /********************************************************
     * C
     * user/home/repo_generator/save_data/C
    *********************************************************/
    src_paths[DIR_C] = append_path(save_data, "C");
    const char *c = src_paths[DIR_C];

        // default Makefile
        src_paths[FILE_DEF_MAKEFILE] = append_path(c, "Makefile");

        // .gitignore
        src_paths[FILE_GITIGNORE] = append_path(c, ".gitignore");

    /********************************************************
     * SRC
     * user/home/repo_generator/save_data/C/src
    *********************************************************/
    src_paths[DIR_SRC] = append_path(c, "src");
    const char *src = src_paths[DIR_SRC];

        // main.c
        src_paths[FILE_MAIN_C] = append_path(src, "main.c");

        // exit_codes.c
        src_paths[FILE_EXIT_CODES_C] = append_path(src, "exit_codes.c");

    /********************************************************
     * INCLUDE
     * user/home/repo_generator/save_data/C/include
    *********************************************************/
    src_paths[DIR_INCLUDE] = append_path(c, "include");
    const char *include = src_paths[DIR_INCLUDE];

        // main.h
        src_paths[FILE_MAIN_H] = append_path(include, "main.h");

        // exit_codes.h
        src_paths[FILE_EXIT_CODES_H] = append_path(include, "exit_codes.h");

    /********************************************************
     * DOCS
     * user/home/repo_generator/save_data/C/docs
    *********************************************************/
    src_paths[DIR_DOCS] = append_path(c, "docs");
    const char *docs = src_paths[DIR_DOCS];

    /********************************************************
     * TESTS
     * user/home/repo_generator/save_data/C/test
    *********************************************************/
    src_paths[DIR_TEST] = append_path(c, "test");
    const char *test = src_paths[DIR_TEST];

        // tests.c
        src_paths[FILE_TESTS] = append_path(test, "tests.c");

        // test_all.c
        src_paths[FILE_TEST_ALL] = append_path(test, "test_all.c");

    /********************************************************
     * TEMPLATES
     * user/home/repo_generator/save_data/C/templates
    *********************************************************/
    src_paths[DIR_TEMPLATES] = append_path(c, "templates");
    const char *templates = src_paths[DIR_TEMPLATES];

END:
    return src_paths;
}