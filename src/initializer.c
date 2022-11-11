#include "initializer.h"

exit_code_t initialize_repo()
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = create_directories();
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_gitignore();
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_makefile();
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

END:
    // TODO: remove all generated content from repo if initialization fails
    return exit_code;
}

exit_code_t create_directories()
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = create_directory("src");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_directory("include");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_directory("docs");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_directory("test");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_gitignore()
{
    return E_SUCCESS;
}

exit_code_t create_makefile()
{
    return E_SUCCESS;
}