#include "file.h"

size_t File_GetFileSize(FILE *file)
{
    size_t size = -1;
    if(file)
    {
        fseek(file, 0, SEEK_END);
        size = ftell(file);
        rewind(file);
    }

    return size;
}

bool File_GetContentFromFile(const char *filename, void *buffer, size_t size)
{
    FILE *file = fopen(filename, "r");
    if(file == NULL)
        return false;

    fread(buffer, 1, size, file);
    
    fclose(file);

    return true;
}