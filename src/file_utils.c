#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

#include "file_utils.h"


char* read_file(const char* path) {
    // open the file
    FILE* file_ptr = fopen(path, "r");
    if (file_ptr == NULL) {
        printf("Failed to open file: %s\n", path);
        return NULL;
    }

    // get the size of the file in bytes
    fseek(file_ptr, 0, SEEK_END);
    long file_size = ftell(file_ptr);
    rewind(file_ptr);

    // allocate memory to store file contents
    // as a pointer dynamically allocated memory gets returned, it must be freed using `free` when finished with
    char* buffer = malloc(file_size + 1); // add 1 for null terminator
    if (buffer == NULL) {
        fclose(file_ptr);
        perror("Error allocating memory for file contents");
        return NULL;
    }

    // read the contents and store them to the buffer
    size_t result = fread(buffer, 1, file_size, file_ptr);
    if (result != file_size) {
        fclose(file_ptr);
        free(buffer);
        perror("Error reading file contents");
        return NULL;
    }

    // null terminate the buffer and close the file
    buffer[file_size] = '\0';
    fclose(file_ptr);

    return buffer;
}
