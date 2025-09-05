#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>

#include "stringlib.h"

char* read_string_console(const char * prompt) {
    return readline(prompt);
}

static char* read_row_from_file(FILE * const file){
    if (!file) {
        return NULL;
    }
    
    char *res = NULL;
    char buf[81] = {0};
    int len = 0;
    int n = 0;
    
    do {
        n = fscanf(file, "%80[^\n]", buf);
        if(n < 0 && !res){
            return NULL;
        }
        else if(n > 0){
            int len_p = strlen(buf);
            int len_s = len + len_p;
            char *new_res = realloc(res, (len_s + 1) * sizeof(char));
            if (!new_res) {
                free(res);
                return NULL;
            }
            res = new_res;
            memcpy(res + len, buf, len_p);
            len = len_s;
        }
        else{
            fscanf(file, "%*c");
        }
    } while(n > 0);

    if(len > 0){
        res[len] = '\0';


    } else{
        res = calloc(1, sizeof(char));
        if (res) {
            res[0] = '\0';
        }
    }
    
    return res;
}

static char *to_lower_register(char * const str) {
    if (!str) {
        return NULL;
    }
    
    size_t i = 0;
    while (str[i]) {
        str[i] = tolower(str[i]);
        i++;
    }

    return str;
}

char* read_process(FILE * const file, char * const source) {
    if (!file) {
        return NULL;
    }

    char *lower_register_source = to_lower_register(strdup(source));
    if (!lower_register_source) {
        return NULL;
    }

    char *str_from_file = read_row_from_file(file);
    if (!str_from_file) {
        free(lower_register_source);
        return NULL;
    }

    char *lower_register_str = to_lower_register(strdup(str_from_file));
    if (!lower_register_str) {
        free(lower_register_source);
        free(str_from_file);
        return NULL;
    }

    if (strstr(lower_register_str, lower_register_source)) {
        free(lower_register_source);
        free(lower_register_str);
        return str_from_file;
    }

    free(lower_register_source);
    free(lower_register_str);
    free(str_from_file);

    return NULL;
}
