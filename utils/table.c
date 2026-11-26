// dynamic table
// From https://www.geeksforgeeks.org/dsa/implementation-on-map-or-dictionary-data-structure-in-c/
#include "table.h"
#include <stdio.h>
#include <string.h>

int t_size = 0;                       // Current number of elements in the map
char t_keys[T_MAX_SIZE][T_MAX_LEN];   // Array to store the keys
char t_values[T_MAX_SIZE][T_MAX_LEN]; // Array to store the values

// Copy src into dest, bounded so a bug can never overflow the buffer
static void t_copy(char dest[T_MAX_LEN], const char *src)
{
    strncpy(dest, src, T_MAX_LEN - 1);
    dest[T_MAX_LEN - 1] = '\0';
}

// Function to get the index of a key in the keys array
int t_getIndex(const char *key)
{
    if (key == NULL)
    {
        return -1;
    }

    for (int i = 0; i < t_size; i++)
    {
        if (strcmp(t_keys[i], key) == 0)
        {
            return i;
        }
    }
    return -1; // Key not found
}

// Function to insert or update a key-value pair in the map
// Returns 0 on success, -1 on invalid argument or when the table is full
int t_insert(const char *key, const char *value)
{
    if (key == NULL || value == NULL)
    {
        return -1;
    }

    // Reject anything that would be truncated: a truncated key could never
    // be looked up again, and a truncated value is silently wrong.
    if (strlen(key) >= T_MAX_LEN || strlen(value) >= T_MAX_LEN)
    {
        return -1;
    }

    int index = t_getIndex(key);
    if (index == -1)
    { // Key not found
        if (t_size >= T_MAX_SIZE)
        { // Table is full
            return -1;
        }
        t_copy(t_keys[t_size], key);
        t_copy(t_values[t_size], value);
        t_size++;
    }
    else
    { // Key found
        t_copy(t_values[index], value);
    }
    return 0;
}

// Function to get the value of a key in the map
// Returns NULL if the key is not found
const char *t_get(const char *key)
{
    int index = t_getIndex(key);
    if (index == -1)
    { // Key not found
        return NULL;
    }
    return t_values[index]; // Key found
}

// Function to print every key-value pair in the map, one per line
void t_print(void)
{
    for (int i = 0; i < t_size; i++)
    {
        printf("%s: %s\n", t_keys[i], t_values[i]);
    }
}
