#include "myalloc.h"
#include <stdlib.h>
#include <sys/mman.h>

#define MMAP_SIZE 1024

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))

void myfree(void *p) {

}

void *myalloc(int size) {

    block *head = NULL;

    if (!head) {
        head = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        head->next = NULL;
        head->size = MMAP_SIZE - PADDED_SIZE(sizeof(block));
        head->in_use = 0;
    }

    return head;
}
