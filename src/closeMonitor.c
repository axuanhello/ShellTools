/*
* Only on Windows platform
*/
#include <Windows.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <powrprof.h>
#pragma comment(lib,"libpowrprof.lib") 
int main(int argc, char** argv) {
    int second = 1;
    int sleep = 0;
    char* pluralSuffix = "";
    
    for (int i = 1; i < argc; ++i) {
        //-t flag, input the execution delay time.
        if (!strcmp(argv[i], "-t")) {
            if (++i < argc) {

                // we can also use atoi() function, but it may not capture some errors.

                second = 0;
                int j = 0;
                for (; argv[i][j] && argv[i][j] >= '0' && argv[i][j] <= '9'; ++j) {
                    second = second * 10 + argv[i][j] - '0';
                    if (second < 0) {
                        errno = 22;
                        perror("'-t' parameter overflow!");
                        exit(-1);
                    }
                }
                if (argv[i][j]) {
                    errno = 22;
                    perror("'-t' parameter should be a nonnegative integer.\n");
                    exit(-1);
                }
            }
        }
        //-s flag, to determine whether the computer should sleep or not.
        else if (!strcmp(argv[i], "-s")) {
            sleep = 1;
        }
    }

    if (second > 1) {
        pluralSuffix = "s";
    }

    if (sleep) {
        printf("Computer will sleep in %d second%s.\n", second, pluralSuffix);
        Sleep(second * 1000);
        SetSuspendState(FALSE, FALSE, FALSE);
    }
    else {
        printf("Monitor will be closed in %d second%s.\n", second,pluralSuffix);
        Sleep(second * 1000);
        PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2);
    }
    
    return 0;
}