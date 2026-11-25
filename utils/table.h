#ifndef TABLE_H
#define TABLE_H

#define MAX_SIZE 1000

extern int size;
extern char keys[MAX_SIZE][100];
extern int values[MAX_SIZE];

int getIndex(char key[]);
void insert(char key[], int value);
int get(char key[]);

#endif