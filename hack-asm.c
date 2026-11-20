#include <stdio.h>
#include <string.h>

// --- UTILITIES --- 

void strip_spaces(char *s)
{
    // 2 pointers - d and s
    // pointer to string
    char *d = s;
    do 
    {
        // skim through strings
        while (*d == ' ' || *d == '\n')
        {
            // skip empty space
            ++d;
        }
        
    // "place" letter that is not whitespace
    // then move both pointer one step    
    } while ((*s++ = *d++));
}

// Simple key-value struct
typedef struct {
    const char *key;
    const char *value;
} DictItem;

#define C_HEAD 011
#define A_HEAD 111
#define A_BIT 0

// define misc table
// A-instruction @, Label
// define comp table
// define dest table
// define jump table

// --- ---------- ----

// Main Assembler logic

char* translate_instruction(char *s)
{
    //16-bit translation
    char intruct[16];

    for(int i = 0; i < strlen(s); i++)
    {

    }

    // TODO do translation
    return "test";
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
    char line[24];

    // Read file line by line
    while(fgets(line, sizeof(line), file)) {
        strip_spaces(line);
        char* instruction = translate_instruction(line);
        printf("%s\n", instruction);
    }
    
    fclose(file);
    return 0;
}