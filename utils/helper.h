#ifndef HELPER_H
#define HELPER_H

#define C_HEAD "011"
#define A_HEAD "111"
#define A_SYMBOL '@'

#define COMP_LEN sizeof(COMP_TABLE) / sizeof(COMP_TABLE[0])
#define DEST_LEN sizeof(DEST_TABLE) / sizeof(DEST_TABLE[0])
#define JUMP_LEN sizeof(JUMP_TABLE) / sizeof(JUMP_TABLE[0])
#define DSYM_LEN sizeof(DEFINED_SYMBOL) / sizeof(DEFINED_SYMBOL[0])

typedef struct {
    const char *key;
    const char *value;
} DictItem;

extern DictItem COMP_TABLE[28];
extern DictItem DEST_TABLE[8];
extern DictItem JUMP_TABLE[8];
extern DictItem DEFINED_SYMBOL[23];

void strip_spaces(char *s);

#endif