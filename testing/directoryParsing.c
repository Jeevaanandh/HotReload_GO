//
// Created by Jeevaanandh Ilayaraja on 07/03/26.
//


#include<stdio.h>
#include<string.h>
#include<dirent.h>


//This is the recursively find directories
void parse(char *path) {
    struct dirent *entry;
    DIR *dir= opendir(path);

    while ((entry= readdir(dir)) != NULL) {
        if (entry->d_name[0]=='.') {
            continue;
        }

        //If it is a directory watch it.
        if (entry->d_type == DT_DIR) {
            char fullpath[1024];
            snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);
            printf("Directory: %s\n", entry->d_name);
            parse(fullpath);

        }

    }

}

int main() {
    parse("./test");
}