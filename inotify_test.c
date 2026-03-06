//
// Created by Jeevaanandh Ilayaraja on 07/03/26.
//

#include<stdio.h>
#include<sys/inotify.h>
#include<string.h>
#include<unistd.h>

#define BUFSIZE 1024
int main() {
    int fd = inotify_init();
    char buf[BUFSIZE];

    int wd= inotify_add_watch(
        fd,
        "./test",
        IN_CREATE | IN_MODIFY | IN_DELETE   // Anytime one of these are triggered, a stuct is returned.
    );

    while(1) {
        //This waits until something is added to the buffer
        //The buffer stores the address to the structs.
        int len= read(fd, buf, BUFSIZE);
        int i=0;

        while (i<len) {
            struct inotify_event *event= (struct inotify_event *) &buf[i];

            if (event->name[0] == '.')    goto incr;  // hidden files
            if (strstr(event->name, "~"))    goto incr;
            if (!(strstr(event->name, ".txt"))) goto incr;



            if (event->mask & IN_CREATE) {
                printf("File Created %s\n", event->name);
            }

            if (event->mask & IN_MODIFY) {

                printf("File Modified %s\n", event->name);
            }

            incr:
            i+= sizeof(struct inotify_event)+event->len;


        }
    }

}