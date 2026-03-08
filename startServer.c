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


//This is to kill all child processes after the user stops the hotreload using crtl+c
void handle_sigint(int sig) {
    printf("Stopping hotreload...\n");

    if (child_pid > 0) {
        killpg(child_pid, SIGTERM);
    }

    _exit(0);
}

void run(char *run_command, char *projectFolder) {
    child_pid=fork();
    if (child_pid<0) {
        printf("Fork failed\n");
        return;
    }

    if (child_pid==0) {
        //Child Process
        // execute the command to start the server.

		if (chdir(projectFolder) != 0) {
          	perror("chdir failed");
          	_exit(1);
    	}


        setpgid(0, 0);

        execl("/bin/sh", "sh", "-c", run_command, NULL);
        perror("exec failed");
        _exit(1);


        // printf("Hello From Child...\n");
        // sleep(10);
        // _exit(0);

    }



}


//THis is the function to run the build command.
int build(char *build_command, char *projectFolder){
	pid_t pid = fork();

	if (pid == 0) {

		if (chdir(projectFolder) != 0) {
          	perror("chdir failed");
          	_exit(1);
    	}

    	execl("/bin/sh", "sh", "-c", build_command, NULL);
    	perror("exec failed");
    	_exit(1);
	}

	int status;
	waitpid(pid, &status, 0);

	if (WIFEXITED(status)) {
        int code = WEXITSTATUS(status);

        if (code == 0) {
            return 1;  // build success
        }
		else {
            return 0;  // build failed
        }
    }

    return 0; // abnormal termination

}




int kill_child() {
    if (child_pid==-1) {
        return 0;
    }

	//Killing the whole process group ie. the child and its children
    killpg(child_pid, SIGTERM);
    //parent acknowledging the exit of the child. If this is not done, the child becomes a Zombie
    waitpid(child_pid, NULL, 0);
    child_pid=-1;

    return 0;

}



//Send the path of the project and the commands (Build and run) to this function
int startServer(char *projectFolder, char *build_cmd, char *run_cmd) {
    int res;
    res= kill_child();

	//Send the project path and the build command to the build() function
	res= build(build_cmd, projectFolder);
	if(res==1){
		//Send the project path and the run command to the run() function
		run(run_cmd, projectFolder);

	}


}

