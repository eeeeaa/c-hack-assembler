#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils/helper.h"
#include "utils/table.h"

// Main Assembler logic

// Initalize
void initialize()
{
    // populate pre-defined symbols
    for (unsigned long i = 0; i < DSYM_LEN; i++)
    {
        t_insert(
            DEFINED_SYMBOL[i].key,
            DEFINED_SYMBOL[i].value);
    }
}

// scan the entire code and insert label to table
void first_pass(FILE *file)
{
    // line buffer
    char line[24];
    int count = 0;

    while (fgets(line, sizeof(line), file))
    {
        // only care about non-blank line
        if (line[0] != '\n')
        {
            strip_spaces(line);

            // Extract tokens
            char *tokens[3] = {NULL, NULL, NULL};
            extract_tokens(line, tokens);

            if (tokens[1] == NULL && tokens[2] == NULL)
            {
                char str[100];
                snprintf(str, sizeof(str), "%d", count + 1);
                t_insert(tokens[0], str);
            }
            else
            {
                count++;
            }
        }
    }

    rewind(file);
}

// scan the entire code
// add variable to table
// substitute label and variable via representation
// translate to binary
// A-instruction - @ -  0, value - 15 bit
// C-instruction - 111 - comp 7 bit - dest 3 bit - jump 3 bit
void second_pass(FILE *file)
{
    FILE *output;
    output = fopen("output/out.hack", "w");

    // line buffer
    char line[24];
    int sym_mem_count = SYM_START;

    while (fgets(line, sizeof(line), file))
    {
        // only care about non-blank line
        if (line[0] != '\n')
        {
            strip_spaces(line);

            // Extract tokens
            char *tokens[3] = {NULL, NULL, NULL};
            extract_tokens(line, tokens);

            // TODO
            if (tokens[1] == NULL && tokens[2] == NULL)
            {
                // skip
                continue;
            }
            else
            {
                if (tokens[0] != NULL && tokens[0][0] == A_SYMBOL && tokens[0][1] == '\0')
                {
                    // A - instruction
                    int value;
                    char *endptr;
                    long parsed = strtol(tokens[1], &endptr, 10);

                    if (tokens[1][0] != '\0' && *endptr == '\0')
                    {
                        // It's a valid integer
                        value = (int)parsed;
                    }
                    else if (t_get(tokens[1]) != NULL)
                    {
                        // Existing variable symbol
                        value = atoi(t_get(tokens[1]));
                    }
                    else
                    {
                        // New variable symbol
                        char buf[16];
                        snprintf(buf, sizeof(buf), "%d", sym_mem_count);
                        t_insert(tokens[1], buf);
                        value = sym_mem_count++;
                    }

                    char *b = to_binary_string(value, 15);
                    fprintf(output, "%s%s\n", A_HEAD, b);
                    free(b);
                }
                else
                {
                    // C - instruction
                }
            }
        }
    }

    fclose(output);
    rewind(file);
}

// Main program
int main(int argc, char *argv[])
{
    if (argc == 1 || argc > 2)
    {
        printf("invalid or empty argument, please pass a hack assembly file as argument");
        return 0;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("assembly file not found");
        return 0;
    }

    initialize();
    first_pass(file);
    //t_print();
    second_pass(file);

    fclose(file);
    return 0;
}