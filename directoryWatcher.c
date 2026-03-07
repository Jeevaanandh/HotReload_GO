//
// Created by Jeevaanandh Ilayaraja on 07/03/26.
//

#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include<sys/inotify.h>
#include <unistd.h>

#define BUFSIZE 1024
int fd;
char buf[BUFSIZE];

void parse(char *path, int flag) {
    struct dirent *entry;
    DIR *dir= opendir(path);

    if (flag==0) {
        int wd= inotify_add_watch(
                    fd,
                    path,
                    IN_CLOSE_WRITE | IN_MOVED_TO | IN_DELETE   // Anytime one of these are triggered, a stuct is returned.
            );
    }

    while ((entry= readdir(dir)) != NULL) {
        if (entry->d_name[0]=='.') {
            continue;
        }

        //If it is a directory watch it.
        if (entry->d_type == DT_DIR) {
            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
            int wd= inotify_add_watch(
                    fd,
                    fullpath,
                    IN_CLOSE_WRITE | IN_MOVED_TO | IN_DELETE   // Anytime one of these are triggered, a stuct is returned.
            );

            parse(fullpath, flag+1);

        }

    }
}


int main() {
    fd = inotify_init();

    parse("./test", 0);

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



            if (event->mask & IN_CLOSE_WRITE) {
                printf("File modified %s\n", event->name);
            }

            if (event->mask & IN_MOVED_TO) {

                printf("File moved %s\n", event->name);
            }

            incr:
            i+= sizeof(struct inotify_event)+event->len;


        }
    }

}
