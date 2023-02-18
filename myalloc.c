#include "myalloc.h"
#include <stdlib.h>
#include <sys/mman.h>
#include <stdio.h>

#define MMAP_SIZE 1024

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))

#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

block *head = NULL;

void *myalloc(int size) {
    size_t padded_block_size = PADDED_SIZE(sizeof(block));

    if (!head) {
        head = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        head->next = NULL;
        head->size = MMAP_SIZE - padded_block_size;
        head->in_use = 0;
    }

    block *current = head;
    while (current) {
        if(!current->in_use && PADDED_SIZE(size) < current->size) {
            current->in_use = 1;
            return PTR_OFFSET(current, padded_block_size);
        }
        current = current->next;
    }
    return NULL;
}

void print_data() {
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

int main(void) {

    {
        head = NULL;
        void *p = NULL;
        head = p;
        print_data();
        p = myalloc(700);
        print_data();
    }

    {
        void *p = NULL;

        head = NULL;
        print_data();
        p = myalloc(16);
        print_data();
        p = myalloc(16);
        printf("%p\n", p);
    }

    return 0;
}
