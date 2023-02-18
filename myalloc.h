#ifndef MYALLOC_H
#define MYALLOC_H

struct block {
    struct block *next;
    int size;     // Bytes
    int in_use;   // Boolean
};

typedef struct block block;

void *myalloc(int size);
//TODO: void myfree(void *p);
void print_data();

#endif
