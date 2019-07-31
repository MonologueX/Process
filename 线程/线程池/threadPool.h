#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include <stdio.h>
#include <pthread.h>
#include "condition.c"

typedef struct task
{
    void *(*pfunc)(void*);
    void *arg;
    struct task *next;
}task_t;

typedef struct threadpool
{
    condition_t cond;
    task_t *first;
    task_t *tail;
    int max_thread;
    int idle;
    int counter;
    int quit;
}threadpool_t;

void threadpool_init(threadpool_t *pool, int max);

void threadpool_add(threadpool_t *pool, void*(*pf)(void*), void *arg);

void threadpool_destroy(threadpool_t *pool);

#endif // __THREADPOOL_H__
