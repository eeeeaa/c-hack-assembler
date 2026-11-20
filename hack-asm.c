#include <stdio.h>
#include <string.h>

// Simple key-value struct
typedef struct {
    const char *key;
    const char *value;
} DictItem;

// define misc table
// A-instruction @, Label
// define comp table
// define dest table
// define jump table

void translate_c_instruction()
{
    // TODO
}

void translate_a_instruction()
{
    // TODO
}

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
    char line[256];

    // Read file line by line
    while(fgets(line, sizeof(line), file)) {
        // TODO: Perform translation
        printf("%s", line);
    }
    
    fclose(file);
    return 0;
}