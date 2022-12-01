#include "src_paths.h"

void free_src_paths(char **src_paths)
{
    for (size_t idx = 0; idx < SRC_NUMBER_OF_CODES; idx++)
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

    // Allocate space for the path array
    char **src_paths = calloc(1, sizeof(**src_paths));
    if (NULL == src_paths)
    {
        free (src_paths);
        src_paths = NULL;
        goto END;
    }

    // Allocate space for each path
    for (size_t idx = 0; idx < SRC_NUMBER_OF_CODES; idx++)
    {
        src_paths[idx] = calloc(1, sizeof(char*));
        if (NULL == src_paths[idx])
        {
            destroy_src_paths(src_paths);
            goto END;
        }
    }

    /********************************************************
     * NAME: REPO_GENERATOR
     * PATH: user/home/repo_generator
    *********************************************************/
    src_paths[SRC_DIR_REPO] = append_path(home, "repo_generator");
    const char *repo = src_paths[SRC_DIR_REPO];

    /********************************************************
     * NAME: SAVE_DATA
     * PATH: user/home/repo_generator/save_data
    *********************************************************/
    src_paths[SRC_DIR_SAVE_DATA] = append_path(repo, "save_data");
    const char *save_data = src_paths[SRC_DIR_SAVE_DATA];

    /********************************************************
     * NAME: C
     * PATH: user/home/repo_generator/save_data/C
    *********************************************************/
    src_paths[SRC_DIR_C] = append_path(save_data, "C");
    const char *c = src_paths[SRC_DIR_C];

        // default Makefile
        src_paths[SRC_FILE_DEF_MAKEFILE] = append_path(c, "Makefile");

        // .gitignore
        src_paths[SRC_FILE_GITIGNORE] = append_path(c, ".gitignore");

    /********************************************************
     * NAME: SRC
     * PATH: user/home/repo_generator/save_data/C/src
    *********************************************************/
    src_paths[SRC_DIR_SRC] = append_path(c, "src");
    const char *src = src_paths[SRC_DIR_SRC];

        // main.c
        src_paths[SRC_FILE_MAIN_C] = append_path(src, "main.c");

        // exit_codes.c
        src_paths[SRC_FILE_EXIT_CODES_C] = append_path(src, "exit_codes.c");

    /********************************************************
     * NAME: INCLUDE
     * PATH: user/home/repo_generator/save_data/C/include
    *********************************************************/
    src_paths[SRC_DIR_INCLUDE] = append_path(c, "include");
    const char *include = src_paths[SRC_DIR_INCLUDE];

        // main.h
        src_paths[SRC_FILE_MAIN_H] = append_path(include, "main.h");

        // exit_codes.h
        src_paths[SRC_FILE_EXIT_CODES_H] = append_path(include, "exit_codes.h");

    /********************************************************
     * NAME: DOCS
     * PATH: user/home/repo_generator/save_data/C/docs
    *********************************************************/
    src_paths[SRC_DIR_DOCS] = append_path(c, "docs");

    /********************************************************
     * NAME: TESTS
     * PATH: user/home/repo_generator/save_data/C/test
    *********************************************************/
    src_paths[SRC_DIR_TEST] = append_path(c, "test");
    const char *test = src_paths[SRC_DIR_TEST];

        // tests.c
        src_paths[SRC_FILE_TESTS] = append_path(test, "tests.c");

        // test_all.c
        src_paths[SRC_FILE_TEST_ALL] = append_path(test, "test_all.c");

    /********************************************************
     * NAME: TEMPLATES
     * NAME: user/home/repo_generator/save_data/C/templates
    *********************************************************/
    src_paths[SRC_DIR_TEMPLATES] = append_path(c, "templates");

END:
    return src_paths;
}