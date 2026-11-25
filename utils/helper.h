#ifndef HELPER_H
#define HELPER_H

#define C_HEAD "011"
#define A_HEAD "111"
#define A_SYMBOL "@"

typedef struct {
    const char *key;
    const char *value;
} DictItem;

extern DictItem COMP_TABLE[28];
extern DictItem DEST_TABLE[8];
extern DictItem JUMP_TABLE[8];

void strip_spaces(char *s);

#endif