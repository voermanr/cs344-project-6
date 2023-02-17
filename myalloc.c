#include "myalloc.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#define MMAP_SIZE 1024

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))

#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

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

    return PTR_OFFSET(head, PADDED_SIZE(sizeof(block)));
}

void print_data(block *head)
{
    block *b = head;

    if (b == NULL) {
        printf("[empty]\n");
        return;
    }

    while (b != NULL) {
        // Uncomment the following line if you want to see the pointer values
        //printf("[%p:%d,%s]", b, b->size, b->in_use? "used": "free");
        printf("[%d,%s]", b->size, b->in_use? "used": "free");
        if (b->next != NULL) {
            printf(" -> ");
        }

        b = b->next;
    }

    printf("\n");
}
