#include "threadPool.h"

#include <stdlib.h>
#include <errno.h>
#include <time.h>

void threadpool_init(threadpool_t *pool, int max)
{
    condition_init(&pool->cond);
    pool->first = NULL;
    pool->tail = NULL;
    pool->max_thread = max;
    pool->idle = 0;
    pool->counter = 0;
    pool->quit = 0;
}

static void*route(void *arg)
{
    threadpool_t *pool = (threadpool_t*)arg;
    int timeout = 0;

    while (1)
    {
        condition_lock(&pool->cond);

        pool->idle++;
        while (pool->first == NULL && pool->quit == 0)
        {
            struct timespec ts;
            clock_gettime(CLOCK_REALTIME, &ts);
            ts.tv_sec += 2;
            int ret = condition_timewait(&pool->cond, &ts);
            if (ret == ETIMEDOUT)
            {
                timeout = 1;
                break;
            }
        }
        pool->idle--;

        if (pool->first != NULL)
        {
            task_t *p = pool->first;
            pool->first = p->next;

            // 防止任务执行太久
            condition_unlock(&pool->cond);
            p->pfunc(p->arg);
            condition_lock(&pool->cond);

            free(p);
        }

        if (pool->first == NULL && timeout == 1)
        {
            condition_unlock(&pool->cond);
            printf("%lu thread timeout\n", pthread_self());
            break;
        }

        if (pool->first == NULL && pool->quit == 1)
        {
            printf("%lu thread destroy!\n", pthread_self());
            pool->counter--;
            if (pool->counter == 0)
            {
                condition_signal(&pool->cond);
            }
            condition_unlock(&pool->cond);
            break;
        }

        condition_unlock(&pool->cond);
    }
    return NULL;
}

void threadpool_add(threadpool_t *pool, void*(*pf)(void*), void *arg)
{
    task_t *newNode = (task_t*)malloc(sizeof(task_t));
    newNode->pfunc = pf;
    newNode->arg = arg;
    newNode->next = NULL;

    condition_lock(&pool->cond);

    if (pool->first == NULL)
        pool->first = newNode;
    else 
        pool->tail->next = newNode;
    pool->tail = newNode;

    if (pool->idle > 0)
    {
        condition_signal(&pool->cond);
    }
    else if (pool->counter < pool->max_thread) 
    {
        pthread_t tid;
        pthread_create(&tid, NULL, route, (void*)pool);
        pool->counter++;
    }

    condition_unlock(&pool->cond);
}

void threadpool_destroy(threadpool_t *pool)
{
    if (pool->quit)
        return;
    condition_lock(&pool->cond);

    pool->quit = 1;
    if (pool->counter > 0)
    {
        if (pool->idle > 0)
        {
            condition_boardcast(&pool->cond);
        }
    }

    while (pool->counter > 0)
    {
        condition_wait(&pool->cond);
    }

    condition_unlock(&pool->cond);
}
