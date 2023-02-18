#include "myalloc.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

int main(void) {

    {
        void *p = NULL;
        print_data(p);
        p = myalloc(64);
        print_data(p);
    }

    {
        void *p = NULL;

        print_data(p);
        p = myalloc(16);
        print_data(p);
        p = myalloc(16);
        printf("%p\n", p);
    }

    return 0;
}