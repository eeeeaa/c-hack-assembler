#ifndef TABLE_H
#define TABLE_H

#define T_MAX_SIZE 1000 // Maximum number of key-value pairs
#define T_MAX_LEN 100   // Maximum length of a key or value (including '\0')

extern int t_size;
extern char t_keys[T_MAX_SIZE][T_MAX_LEN];
extern char t_values[T_MAX_SIZE][T_MAX_LEN];

int t_getIndex(const char *key);
int t_insert(const char *key, const char *value);
const char *t_get(const char *key);
void t_print(void);

#endif
