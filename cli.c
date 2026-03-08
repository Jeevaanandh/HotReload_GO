#include <stdio.h>
#include <getopt.h>
#include <unistd.h>
#include<signal.h>
#include "startServer.h"
#include "directoryWatcher.h"


int main(int argc, char *argv[]) {
    signal(SIGINT, handle_sigint);

    char *root = NULL;
    char *build_cmd = NULL;
    char *run_cmd = NULL;

    int opt;

    struct option long_options[] = {
        {"root",  required_argument, 0, 'r'},
        {"build", required_argument, 0, 'b'},
        {"exec",   required_argument, 0, 'e'},
        {0,0,0,0}
    };

    while ((opt = getopt_long(argc, argv, "", long_options, NULL)) != -1) {

        switch (opt) {
            case 'r':
                root = optarg;
                break;

            case 'b':
                build_cmd = optarg;
                break;

            case 'e':
                run_cmd = optarg;
                break;

            default:
                printf("Unknown option\n");
                return -1;
        }
    }



    watcher(root, build_cmd, run_cmd);
}