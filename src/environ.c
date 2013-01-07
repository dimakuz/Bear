// This file is distributed under MIT-LICENSE. See COPYING for details.

#include "environ.h"
#include "stringarray.h"

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char const * * bear_env_insert(char const * envs[], char const * key, char const * value)
{
    if (0 == value)
    {
        perror("getenv");
        exit(EXIT_FAILURE);
    }
    // create new env value
    char * env = 0;
    if (-1 == asprintf(&env, "%s=%s", key, value))
    {
        perror("asprintf");
        exit(EXIT_FAILURE);
    }
    // remove environments which has the same key
    size_t const key_length = strlen(key) + 1;
    char const * * it = envs;
    for (; (envs) && (*it); ++it)
    {
        if (0 == strncmp(env, *it, key_length))
        {
            envs = bear_strings_remove(envs, *it);
            it = envs;
        }
    }
    return bear_strings_append(envs, env);
}

