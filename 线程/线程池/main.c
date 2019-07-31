#include "threadPool.c"
#include <stdlib.h>
#include <unistd.h>

static void *myroute(void *arg)
{
    int id = *(int*)arg;
    free(arg);
    printf("%lu thread runing %d\n", pthread_self(), id);
    sleep(1);
    return NULL;
}

int main()
{
    threadpool_t pool;
    threadpool_init(&pool, 3);
    for (int i = 0; i < 10; i++)
    {
        int *p = (int*)malloc(sizeof(int));
        *p = i;
        threadpool_add(&pool, myroute, p);
    }
    threadpool_destroy(&pool);
    return 0;
}
