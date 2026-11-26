#include "helper.h"
#include <stdlib.h>
#include <string.h>

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

char *to_binary_string(int n, int bit)
{
    if (bit <= 0)
    {
        return NULL;
    }

    char *string = malloc(bit + 1);
    if (!string)
    {
        return NULL;
    }

    unsigned int u = (unsigned int)n;
    for (int i = bit - 1; i >= 0; i--)
    {
        string[i] = (u & 1) + '0';
        u >>= 1;
    }

    string[bit] = '\0';
    return string;
}

// Extract tokens
void extract_tokens(char *s, char *tokens[3])
{
    size_t len = strlen(s);
    // (XXX) -> [XXX, NULL, NULL]
    if (len >= 2 && s[0] == '(' && s[len - 1] == ')')
    {
        // strip last char
        s[len - 1] = '\0';
        tokens[0] = s + 1;
        tokens[1] = NULL;
        tokens[2] = NULL;
        return;
    }

    if (s[0] == A_SYMBOL)
    {
        //@value = [@, value]
        tokens[0] = "@";
        tokens[1] = s + 1;
        return;
    }

    // dest=comp;jump --> [dest,comp,jump]
    tokens[0] = "null";
    tokens[1] = s;
    tokens[2] = "null";

    char *semi = strchr(s, ';');
    if (semi)
    {
        *semi = '\0';
        tokens[2] = semi + 1;
    }

    char *eq = strchr(s, '=');
    if (eq)
    {
        *eq = '\0';
        tokens[0] = s;
        tokens[1] = eq + 1;
    }
}

// define comp table
// a = 0 and a = 1 --> 7 bits
DictItem COMP_TABLE[28] = {
    {"0", "0101010"},
    {"1", "0111111"},
    {"-1", "0111010"},
    {"D", "0001100"},
    {"A", "0110000"},
    {"M", "1110000"},
    {"!D", "0001101"},
    {"!A", "0110001"},
    {"!M", "1110001"},
    {"-D", "0001111"},
    {"-A", "0110011"},
    {"-M", "1110011"},
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
    {"M", "001"},
    {"D", "010"},
    {"MD", "011"},
    {"A", "100"},
    {"AM", "101"},
    {"AD", "110"},
    {"AMD", "111"},
};
// define jump table
DictItem JUMP_TABLE[8] = {
    {"null", "000"},
    {"JGT", "001"},
    {"JEQ", "010"},
    {"JGE", "011"},
    {"JLT", "100"},
    {"JNE", "101"},
    {"JLE", "110"},
    {"JMP", "111"},
};

// define pre-defined symbol
DictItem DEFINED_SYMBOL[23] = {
    {"SP", "0"},
    {"LCL", "1"},
    {"ARG", "2"},
    {"THIS", "3"},
    {"THAT", "4"},
    {"R0", "0"},
    {"R1", "1"},
    {"R2", "2"},
    {"R3", "3"},
    {"R4", "4"},
    {"R5", "5"},
    {"R6", "6"},
    {"R7", "7"},
    {"R8", "8"},
    {"R9", "9"},
    {"R10", "10"},
    {"R11", "11"},
    {"R12", "12"},
    {"R13", "13"},
    {"R14", "14"},
    {"R15", "15"},
    {"SCREEN", "16384"},
    {"KBD", "24576"},
};
