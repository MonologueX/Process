#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handler(int s)
{
    (void)s;
    printf("\033[0m");
    exit(0);
}

int main()
{
    signal(SIGINT, handler);
    for (int i = 0; ; i++)
    {
        printf("\033[%d;20H", 5+i%7);
        printf("\033[3%dm\033[47mxinwenhuayu", i%6);
        // \033[3xm 字体前景颜色
        // \033[4xm 字体背景颜色
        printf("\033[%d;20H", 5+(i-1)%7);
        printf("            ");
        fflush(stdout);
        printf("\033[?25l");
        printf("\033[0m");
        usleep(100);
    }
    return 0;
}
