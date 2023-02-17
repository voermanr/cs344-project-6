#include "myalloc.h"
#include <stdlib.h>

int main(void) {


    void *p = NULL;
    myfree(p);

    myalloc(1);

    return 0;
}