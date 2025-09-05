#include <stdio.h>
#include <stdlib.h>

#include "../lib/stringlib.h"

#define STRING_OK 1
#define PROMPT_FILENAME "Enter filename: "
#define PROMPT_SOURCE "Enter source string: "

int main(void) {
    while (STRING_OK) {
        char *filename = read_string_console(PROMPT_FILENAME);
        if (!filename) {
            return 1;
        }

        FILE *file = fopen(filename, "r");
        if (!file) {
            perror("fopen");   
            free(filename);
            continue;
        }

        char *source = read_string_console(PROMPT_SOURCE);
        if (!source) {
            free(filename);
            return 1;
        }
        
        while (!feof(file)) {
            char *str_from_file = read_process(file, source);
            if (str_from_file) {
                printf("%s\n", str_from_file);
                free(str_from_file);
            }
        }

        free(filename);
        free(source);
    }

    return 0; 
}
