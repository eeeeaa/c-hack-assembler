#include <stdio.h>
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
}

// scan the entire code
// add variable to table
// substitute label and variable via representation
// translate to binary
void second_pass(FILE *file)
{
    // line buffer
    char line[24];

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
        }
    }
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
    t_print();
    // second_pass(file);

    // TODO create binary file

    fclose(file);
    return 0;
}