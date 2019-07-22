#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main()
{
//    printf("printf\n");
//    fprintf(stdout, "fprintf\n");
//    const char* msg = "write\n";
//    write(1, msg, strlen(msg));
//    fork();
    int i = 0;
    for (; i < 2; i++)
    {
        printf("a");
        fork();
    }
    return 0;
}
