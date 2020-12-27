#ifndef FILE_H_
#define FILE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/**
 * @brief 
 * 
 * @param file 
 * @return size_t 
 */
size_t File_GetFileSize(FILE *file);

/**
 * @brief 
 * 
 * @param filename 
 * @param buffer 
 * @param size 
 * @return true 
 * @return false 
 */
bool File_GetContentFromFile(const char *filename, void *buffer, size_t size);


#endif /* FILE_H_ */
