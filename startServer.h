//
// Created by Jeevaanandh Ilayaraja on 07/03/26.
//

#ifndef HOTRELOAD_GO_STARTSERVER_H
#define HOTRELOAD_GO_STARTSERVER_H

int startServer(char *projectFolder, char *build_cmd, char *run_cmd);
void handle_sigint(int sig);

#endif //HOTRELOAD_GO_STARTSERVER_H