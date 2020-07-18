#include "stack.h"

int  main(void)
{
    
    stack *s;
    int n = 6;
    InitStack(s);
    for (int i = 0; i < n; i++){
        push(s, i);
    }
    printStack(s);
    for (int i = 0; i < n-1; i++){
        int v = pop(s);
        printf("%d\n", v);
    }
    printf("%d\n", s->len);
    free(s->base);
    return 0;
}