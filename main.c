#include "myalloc.h"
#include <stdlib.h>
#include <assert.h>

int main(void) {


    void *p = NULL;
    myfree(p);

    //returns non null ptr
    assert(myalloc(1));

    //
    {
        block *myalloc_return = myalloc(1);

        assert(myalloc_return->in_use == 0);
        assert(myalloc_return->next == NULL);
        assert(myalloc_return->size > 0);
    }

    return 0;
}