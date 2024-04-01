/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** main
*/
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <signal.h>
#include "client.h"
#include <string.h>
#include <fcntl.h>

static bool connect_to_server(client_t *client)
{
    int domain = AF_INET;
    int type = SOCK_STREAM;
    int protocol = 0;
    struct sockaddr_in serveraddr;
    int len;

    client->cli_fd = socket(domain, type, protocol);
    if (!client->cli_fd) {
        perror("socket failed");
        return false;
    }
    serveraddr.sin_family = domain;
    serveraddr.sin_port = htons(8888);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    len = sizeof(serveraddr);
    if (connect(client->cli_fd, (struct sockaddr *)&serveraddr, len) != 0) {
        perror("connection failed");
        return false;
    }
    return true;
}

static bool client_logic(client_t *client)
{
    fd_set rdfds;
    fd_set wrtfds;
    char *tmp;

    if (!connect_to_server(client))
        return false;
    while (1) {
        FD_ZERO(&wrtfds);
        FD_ZERO(&rdfds);
        FD_SET(client->cli_fd, &rdfds);
        FD_SET(client->cli_fd, &wrtfds);
        FD_SET(STDIN_FILENO, &rdfds);

        if (!select(client->cli_fd + 1, &rdfds, &wrtfds, NULL, NULL))
            break;
        if (FD_ISSET(client->cli_fd, &rdfds)) {
            tmp = read_flow(client->cli_fd, true);
            write(1, tmp, strlen(tmp));
            free(tmp);
        }
        if (FD_ISSET(client->cli_fd, &wrtfds)) {
            if (FD_ISSET(STDIN_FILENO, &rdfds)) {
                tmp = read_flow(STDIN_FILENO, false);
                write(client->cli_fd, tmp, (strlen(tmp) - 1));
                write(client->cli_fd, "\r\n", 2);
                free(tmp);
            }
        }
        
    }
    close(client->cli_fd);
    return true;
}

int main(int ac, char **av)
{
    client_t client;
    int ret = 0;

    ret = parse_client(ac, av, &client);
    if (ret != 0) {
        if (ret == 1)
            return 0;
        return ret;
    }
    if (!client_logic(&client))
        return 84;
    free(client.ip);
    return ret;
}
