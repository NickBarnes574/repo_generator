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
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = create_file(".gitignore", "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file(".gitignore", gitignore);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_makefile()
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = create_file("Makefile", "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file("Makefile", Makefile);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_exit_codes()
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = create_file("/src/exit_codes.c", "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file("/src/exit_codes.c", exit_codes_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_file("/include/exit_codes.h", "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file("/include/exit_codes.h", exit_codes_h);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}

exit_code_t create_main()
{
    exit_code_t exit_code = E_DEFAULT_ERROR;

    exit_code = create_file("/src/main.c", "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file("/src/main.c", main_c);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = create_file("/include/main.h", "w");
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = write_to_file("/include/main.h", main_h);
    if (E_SUCCESS != exit_code)
    {
        goto END;
    }

    exit_code = E_SUCCESS;
END:
    return exit_code;
}