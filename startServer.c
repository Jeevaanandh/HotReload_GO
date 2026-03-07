//
// Created by Jeevaanandh Ilayaraja on 07/03/26.
//

#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<stdlib.h>

int child_pid=-1;

void run() {
    child_pid=fork();
    if (child_pid<0) {
        printf("Fork failed\n");
        return;
    }

    if (child_pid==0) {
        //Child Process
        // execute the command to start the server.

        /*
        char *args[] = {"echo", "Hello From Child Process", NULL};
        execv("/bin/echo", args);
        perror("execv failed");
        */
        printf("Hello From Child...\n");
        sleep(10);
        _exit(0);
    }



}


int kill_child() {
    if (child_pid==-1) {
        return 0;
    }

    kill(child_pid, SIGKILL);
    //parent acknowledging the exit of the child. If this is not done, the child becomes a Zombie
    waitpid(child_pid, NULL, 0);
    child_pid=-1;

    return 0;

}


int startServer() {
    int res;
    res= kill_child();

    run();
}