#ifndef MYALLOC_H
#define MYALLOC_H

struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};

typedef struct block block;

void *myalloc(int size);
void myfree(void *p);

void print_data();

void split_space(block *current, int free_space);

void *find_space(int size, block *current);

void first_time();

#endif
