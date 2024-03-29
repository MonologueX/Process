#ifndef __CONDITION_H__
#define __CONDITION_H__

#include <stdio.h>
#include <pthread.h>

typedef struct condition 
{
    pthread_mutex_t pmutex;
    pthread_cond_t pcond;
}condition_t;

int condition_init(condition_t *cond);
int condition_lock(condition_t *cond);
int condition_unlock(condition_t *cond);
int condition_wait(condition_t *cond);
int condition_timewait(condition_t *cond, struct timespec *abstime);
int condition_signal(condition_t *cond);
int condition_boardcast(condition_t *cond);
int condition_destroy(condition_t *cond);

#endif // __CONDITION_H__
