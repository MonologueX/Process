#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <sys/types.h>

///////////////////////////////////////////////
//  sigaction
///////////////////////////////////////////////
void handler(int s)
{
    printf("recv:%d\n", s);
}

int main()
{
    struct sigaction act;
    act.sa_handler = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGINT, &act, NULL);
    // signal(SIGINT, handler);

    for ( ; ; )
        pause();
}

//void handler(int s)
//{
//    (void)s;
//    printf("enter\n");
//    sleep(5);
//    printf("outer\n");
//}
//
//int main()
//{
//    signal(SIGINT, handler);
//    while (1)
//        pause();
//    return 0;
//}

///////////////////////////////////////////////
//  mysleep
///////////////////////////////////////////////
//void handler(int s)
//{
//    (void)s;
//}
//
//int mysleep(int sec)
//{
//    signal(SIGALRM, handler);
//    sigset_t set, old;
//    sigemptyset(&set);
//    sigemptyset(&old);
//    sigaddset(&set, SIGALRM);
//    sigprocmask(SIG_BLOCK, &set, NULL);
//    alarm(sec);
//
//    sigset_t pset;
//    sigemptyset(&pset);
//    sigsuspend(&pset);
//    sigprocmask(SIG_UNBLOCK, &pset, NULL);
//    // pause();
//    int ret = alarm(0);
//    return ret;
//}
//
//int main()
//{
//    mysleep(3);
//    printf("3 sec\n");
//    return 0;
//}

//void handler_quit(int s)
//{
//    sigset_t set;
//    sigemptyset(&set);
//    sigaddset(&set, SIGINT);
//    sigprocmask(SIG_UNBLOCK, &set, NULL);
//}
//
//void handler(int s)
//{
//    printf("recv: %d", s);
//}
//
//int main()
//{
//    signal(SIGINT, handler);
//    signal(SIGQUIT, handler_quit);
//    sigset_t set;
//    sigemptyset(&set);
//    sigaddset(&set, SIGINT);
//    sigprocmask(SIG_BLOCK, &set, NULL);
//    for ( ; ; )
//    {
//        sigset_t pset;
//        sigemptyset(&pset);
//        sigpending(&pset);
//        for (int i = 1; i < _NSIG; i++)
//        {
//            if (sigismember(&pset, i))
//                printf("1");
//            else 
//                printf("0");
//        }
//        printf("\n");
//        sleep(1);
//    }
//    return 0;
//}

///////////////////////////////////////////////
//  可重入不可重入
///////////////////////////////////////////////
//struct TEST
//{
//    int a;
//    int b;
//    int c;
//};
//
//struct TEST g_data;
//
//void handler(int s)
//{
//    (void)s;
//    if (g_data.a != g_data.b || g_data.a != g_data.c || g_data.b !=g_data.c)
//    {
//        printf("%d, %d, %d\n", g_data.a, g_data.b, g_data.c);
//    }
//}
//
//int main()
//{
//    signal(SIGALRM, handler);
//    struct TEST one = {1, 1, 1};
//    struct TEST zero = {0, 0, 0};
//    struct itimerval it;
//    it.it_value.tv_sec = 0;
//    it.it_value.tv_usec = 1;
//    it.it_interval.tv_sec = 1;
//    it.it_interval.tv_usec = 0;
//    setitimer(ITIMER_REAL, &it, NULL);
//    for ( ; ; )
//    {
//        g_data = one;
//        g_data = zero;
//    }
//    return 0;
//}


///////////////////////////////////////////////
//  SIGCHILD
///////////////////////////////////////////////
//void handler(int s)
//{
//    (void)s;
//    wait(NULL);
//}
//int main()
//{
//    signal(SIGCHLD, handler);
//    pid_t pid = fork();
//    if (pid == 0)
//    {
//        for (int i = 0; i < 5; i++)
//        {
//            printf("$");
//            fflush(stdout);
//            sleep(1);
//        }
//        exit(0);
//    }
//    else 
//    {
//        for ( ; ; )
//        {
//            printf(".");
//            fflush(stdout);
//            sleep(1);
//        }
//    }
//    return 0;
//}

///////////////////////////////////////////////
//  定时器
///////////////////////////////////////////////
//void handler(int s)
//{
//    printf("recv: %d\n", s);
//}
//
//int main()
//{
//    signal(SIGALRM, handler);
//    struct itimerval it;
//    it.it_value.tv_sec = 0;
//    it.it_value.tv_usec = 1;
//    it.it_interval.tv_sec = 1;
//    it.it_interval.tv_usec = 0;
//    setitimer(ITIMER_REAL, &it, NULL);
//    for ( ; ; )
//    {
//        pause();
//    }
//    return 0;
//}

///////////////////////////////////////////////
//  8
///////////////////////////////////////////////
//void handler(int signo)
//{
//    printf("signo: %d\n", signo);
//}
//
//int main()
//{
//    // signal(11, handler);
//    // int *p;
//    // p = 10;
//    // *p = 10;
//    
//    // signal(8, handler);
//    int a = 10;
//    a /= 0;
//    return 0;
//}

///////////////////////////////////////////////
//  alarm
///////////////////////////////////////////////
//int f = 0;
//int t = 0;
//void handler(int s)
//{
//    (void)s;
//    printf("时间到！\n");
//    printf("正确: %d", t);
//    printf("错误: %d", f);
//    exit(0);
//}
//
//int main()
//{
//    signal(SIGALRM, handler);
//    alarm(20);
//    
//    for (int i = 0; i < 10; i++)
//    {
//        int left = rand() % 10;
//        int right = rand() % 10;
//        printf("%d + %d = ", left, right);
//        int ret = 0;
//        scanf("%d", &ret);
//        if (left + right == ret)
//            t++;
//        else 
//            f++;
//    }
//    printf("太厉害了！\n");
//    printf("正确: %d", t);
//    printf("错误: %d", f);
//    return 0;
//}

//void handler(int s)
//{
//    (void)s;
//    printf("起床了\n");
//}
//
//int main()
//{
//    signal(SIGALRM, handler);
//    alarm(5);
//    
//    for ( ; ; )
//        pause();
//    return 0;
//}

///////////////////////////////////////////////
//  pause
///////////////////////////////////////////////
//void handler(int s)
//{
//    printf("recv %d\n", s);
//    sleep(2);
//    printf("finush\n");
//}
//
//int main()
//{
//    signal(SIGINT, handler);
//    for ( ; ; )
//    {
//        pause();
//        printf("pause return\n");
//    }
//    return 0;
//}

///////////////////////////////////////////////
//  kill
///////////////////////////////////////////////
//void handler(int s)
//{
//    printf("recv %d\n", s);
//    exit(0);
//}
//
//int main()
//{
//    signal(SIGUSR1, handler);
//    pid_t pid = fork();
//    if (pid == 0)
//    {
//        sleep(3);
//        kill(getppid(), SIGUSR1);
//    }
//    else 
//    {
//        for ( ; ; )
//        {
//            printf(".");
//            fflush(stdout);
//            sleep(1);
//        }
//    }
//    return 0;
//}

///////////////////////////////////////////////
//  父子进程
///////////////////////////////////////////////
//void handler(int signo)
//{
//    (void)signo;
//    printf("你杀不死我");
//}
//
//int main()
//{
//    __sighandler_t old;
//    old = signal(SIGINT, handler);
//    if (old == SIG_ERR)
//    {
//        perror("signal");
//        exit(1);
//    }
//
//    if (fork() == 0)
//    {
//        for ( ; ; )
//        {
//            printf("#");
//            fflush(stdout);
//            sleep(1);
//        }
//    }
//    else 
//    {
//        while ( getchar() != '\n' );
//        signal(SIGINT, old);
//        for ( ; ; )
//        {
//            printf("#");
//            fflush(stdout);
//            sleep(1);
//        }
//    }
//    //while ( getchar() != '\n' );
//    //signal(SIGINT, old);
//    //for ( ; ; )
//    //{
//    //    printf("#");
//    //    fflush(stdout);
//    //    sleep(1);
//    //}
//    return 0;
//}
