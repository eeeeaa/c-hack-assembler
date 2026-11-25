#include <stdio.h>
#include <string.h>
#include "utils/helper.h"
#include "utils/table.h"

// Main Assembler logic


// Extract tokens

// Translation
void initialize() {}
void first_pass() {}
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
            // Initialize - initialize table and pre-defined symbol
            // First pass - find all labels
            // Second pass - find all variables and translate to binary file
        }
    }
    
    fclose(file);
    return 0;
}