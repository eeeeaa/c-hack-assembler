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
#define A_SYMBOL "@"

// define comp table
DictItem COMP_TABLE[28] = {
    {"0",   "0101010"},
    {"1",   "0111111"},
    {"-1",  "0111010"},
    {"D",   "0001100"},
    {"A",   "0110000"},
    {"M",   "1110000"},
    {"!D",  "0001101"},
    {"!A",  "0110001"},
    {"!M",  "1110001"},
    {"-D",  "0001111"},
    {"-A",  "0110011"},
    {"-M",  "1110011"},
    {"D+1", "0011111"},
    {"A+1", "0110111"},
    {"M+1", "1110111"},
    {"D-1", "0001110"},
    {"A-1", "0110010"},
    {"M-1", "1110010"},
    {"D+A", "0000010"},
    {"D+M", "1000010"},
    {"D-A", "0010011"},
    {"D-M", "1010011"},
    {"A-D", "0000111"},
    {"M-D", "1000111"},
    {"D&A", "0000000"},
    {"D&M", "1000000"},
    {"D|A", "0010101"},
    {"D|M", "1010101"},
};
// define dest table
DictItem DEST_TABLE[8] = {
    {"null", "000"},
    {"M",    "001"},
    {"D",    "010"},
    {"MD",   "011"},
    {"A",    "100"},
    {"AM",   "101"},
    {"AD",   "110"},
    {"AMD",  "111"},
};
// define jump table
DictItem JUMP_TABLE[8] = {
    {"null", "000"},
    {"JGT",  "001"},
    {"JEQ",  "010"},
    {"JGE",  "011"},
    {"JLT",  "100"},
    {"JNE",  "101"},
    {"JLE",  "110"},
    {"JMP",  "111"},
};

// --- ---------- ----

// Main Assembler logic

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
        strip_spaces(line);
        // Initialize - initialize table and pre-defined symbol
        // First pass - find all labels
        // Second pass - find all variables and translate to binary file
    }
    
    fclose(file);
    return 0;
}