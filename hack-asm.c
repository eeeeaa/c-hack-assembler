#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils/helper.h"
#include "utils/table.h"

// Main Assembler logic


// Extract tokens
void extract_tokens(char *s, char *tokens[3]) {
   size_t len = strlen(s);
    // (XXX) -> [XXX, NULL, NULL]
    if (len >= 2 && s[0] == '(' && s[len - 1] == ')') {
        //strip last char
        s[len - 1] = '\0';
        tokens[0] = s + 1;
        tokens[1] = NULL;
        tokens[2] = NULL;
        return;
    }

     if(s[0] == A_SYMBOL) {
        //@value = [@, value]
        tokens[0] = "@";
        tokens[1] = s + 1;
        return;
     }

    //dest=comp;jump --> [dest,comp,jump]
    tokens[0] = "null";
    tokens[1] = s;
    tokens[2] = "null";

    char *semi = strchr(s, ';');
    if(semi) {
        *semi = '\0';
        tokens[2] = semi + 1;
    }

    char *eq = strchr(s, '=');
    if(eq) {
        *eq = '\0';
        tokens[0] = s;
        tokens[1] = eq + 1;
    }
}

// Translation
void initialize() {
    // populate pre-defined symbols
    for(unsigned long i = 0; i < DSYM_LEN;i++) {
        t_insert(
            DEFINED_SYMBOL[i].key,
            DEFINED_SYMBOL[i].value
        );
    }
}

// scan the entire code and insert label to table
void first_pass() {}

// scan the entire code
// add variable to table
// substitute label and variable via representation
// translate to binary
void second_pass() {}

// Main program
int main(int argc, char *argv[])
{
    if(argc == 1 || argc > 2) {
        printf("invalid or empty argument, please pass a hack assembly file as argument");
        return 0;
    }
    FILE *file = fopen(argv[1], "r");
    if(file == NULL) {
        printf("assembly file not found");
        return 0;
    }
    
    // line buffer
    char line[24];

    // Read file line by line
    while(fgets(line, sizeof(line), file)) {
        // only care about non-blank line
        if(line[0] != '\n') { 
            strip_spaces(line);
            //printf("%s\n", line);
            // Extract tokens
            char *tokens[3] = {NULL, NULL, NULL};
            extract_tokens(line, tokens);

            for(int i = 0; i < 3; i++) {
                printf("[%s]", tokens[i]);
            }
            // Initialize - initialize table and pre-defined symbol
            // First pass - find all labels
            // Second pass - find all variables and translate to binary file
        }
    }
    
    fclose(file);
    return 0;
}