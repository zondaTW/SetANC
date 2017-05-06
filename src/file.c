#include <stdio.h>

#include "file.h"
#include "types.h"

int file_exists(char const * filename) {
    if (FILE * file = fopen(filename, "r"))
    {
        fclose(file);
        return TRUE;
    }
    return FALSE;
}

int create_file(char const * filename) {
    if (FILE * file = fopen(filename, "a"))
    {
        fclose(file);
        return TRUE;
    }
    return FALSE;
}