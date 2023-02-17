#include "myalloc.h"
#include <stdlib.h>
#include <assert.h>

int main(void) {

    void *p = NULL;
    myfree(p);

    print_data(p);
    p = myalloc(64);
    print_data(p);

    //returns non null ptr
    assert(myalloc(1));

    //


    return 0;
}