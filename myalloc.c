#include "myalloc.h"
#include <sys/mman.h>
#include <stdio.h>

#define MMAP_SIZE 1024

#define ALIGNMENT 16   // Must be power of 2
#define GET_PAD(x) ((ALIGNMENT - 1) - (((x) - 1) & (ALIGNMENT - 1)))

#define PADDED_SIZE(x) ((x) + GET_PAD(x))

#define PTR_OFFSET(p, offset) ((void*)((char *)(p) + (offset)))

#define PADDED_BLOCK_SIZE PADDED_SIZE(sizeof(block))

block *head = NULL;

void *myalloc(int size) {
    if(!head) first_time();

    block *current = head;
    return find_space(size, current);
}

void myfree(void *p) {
    block *cur = head;
    block *pblock = p - PADDED_BLOCK_SIZE;
    while(cur) {
        if (cur->in_use && pblock == cur){
            cur->in_use = 0;
        }

        cur = cur->next;
    }
}

void first_time() {
    head = mmap(NULL, MMAP_SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    head->next = NULL;
    head->size = MMAP_SIZE - PADDED_BLOCK_SIZE;
    head->in_use = 0;
}

void *find_space(int size, block *current) {
    int padded_size = PADDED_SIZE(size);

    while (current) {
        int free_space = current->size - PADDED_BLOCK_SIZE;
        if(!current->in_use && padded_size <= free_space) {
            //Size < free - block size
            if (padded_size < free_space) {
                split_space(current, padded_size);
            }
            current->in_use = 1;

            return PTR_OFFSET(current, PADDED_BLOCK_SIZE);
        }
        current = current->next;
    }
    return NULL;
}

void split_space(block *current, int desired_size) {
    int current_size = current->size;
    desired_size = PADDED_SIZE(desired_size);

    current->in_use = 1;
    current->size = PADDED_SIZE(desired_size);
    current->next = current + desired_size;

    block *next = current->next;
    next->in_use = 0;
    next->size = current_size - desired_size - PADDED_BLOCK_SIZE;
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
        p = myalloc(512);
        print_data();

        myfree(p);
        print_data();
    }

    {
        head = NULL;
        myalloc(10);
        print_data();
        myalloc(20);
        print_data();
        myalloc(30);
        print_data();
        myalloc(40);
        print_data();
        myalloc(50);
        print_data();
    }

    {
        head = NULL;
        void *p;

        myalloc(10);
        print_data();
        p = myalloc(20);
        print_data();
        myalloc(30);
        print_data();
        myfree(p);
        print_data();
        myalloc(40);
        print_data();
        myalloc(10);
        print_data();
    }

    return 0;
}
