
#include <stdio.h>
#include <time.h>
#include "MBTree.h"
 
int main(int argc, const char * argv[]) {
    MBTree T;
    T = Initialize();
    
    clock_t c1 = clock();
    int i = 100;
    while (i > 0)
        T = Insert(T, i--);
    clock_t c2 = clock();
    unsigned long t0 = (c2 - c1)/CLOCKS_PER_SEC;
    /*i = 50000001;
    while (i < 100000000)
        T = Insert(T, i++);
    clock_t c3 = clock();
    unsigned long t1 = (c3 - c2)/CLOCKS_PER_SEC;
    i = 100000000;
    while (i > 100)
        T = Remove(T, i--);
    clock_t c4 = clock();
    unsigned long t2 = (c4 - c3)/CLOCKS_PER_SEC;*/
    Travel(T);
    Retrieval(T, 100);
    Retrieval(T, 101);
    /*clock_t c5 = clock();
    unsigned long t3 = (c5 - c4)/CLOCKS_PER_SEC;
    Destroy(T);
    clock_t c6 = clock();
    unsigned long t4 = (c6 - c5)/CLOCKS_PER_SEC;
    
    printf("\n用时： %lu秒\n%lu秒\n%lu秒\n%lu秒\n%lu秒\n",t0, t1, t2, t3, t4);*/
    return 0;
}
