#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

class MyShell
{
public:
    MyShell()
    {
    }

    void Run()
    {
        _Run();
    }

    ~MyShell()
    {
    }

private:
    void _Run()
    {
        while (1)
        {
            PrintUser();
            fflush(stdout);
            fgets(m_command, 1024, stdin);
            m_command[strlen(m_command)-1] = 0;
            SubStr();
            pid_t pid = fork();
            if (pid < 0)
            {
            }
            else if (pid == 0)
            {
                execvp(myargv[0], myargv);
            }
            else 
            {
                waitpid(pid, nullptr, 0);
            }
        }
    }
    void PrintUser()
    {
        std::cout << "[ch@monoluge shell]> ";
    }
    void SubStr()
    {
        int i = 0;
        myargv[i] = strtok(m_command, " ");
        i++;
        while (1)
        {
            char* p = strtok(nullptr, " ");
            if (nullptr == p)
            {
                myargv[i] = nullptr;
                break;
            }
            myargv[i] = p;
            i++;
        }
    }
private:
    char m_command[1024];
    char *myargv[32];
};


int main()
{
    MyShell shell;
    shell.Run();
    return 0;
}
