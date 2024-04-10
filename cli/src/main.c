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
#include <sys/select.h>
#include "shared.h"

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

static void set_fds(fd_set *wrtfds, fd_set *rdfds, client_t *client)
{
    FD_ZERO(wrtfds);
    FD_ZERO(rdfds);
    FD_SET(client->cli_fd, rdfds);
    FD_SET(client->cli_fd, wrtfds);
    FD_SET(STDIN_FILENO, rdfds);
}

static void read_server(client_t *client, bool *issue)
{
    char *tmp;

    tmp = read_flow(client->cli_fd, true);
    if (!tmp && !(*issue)) {
        (*issue) = true;
        return;
    }
    handle_response(client, tmp);
    free(tmp);
}

static void uinput(client_t *client, fd_set *rdfds, bool *issue)
{
    char *tmp;

    if (FD_ISSET(STDIN_FILENO, rdfds)) {
        tmp = read_flow(STDIN_FILENO, false);
        if (!tmp && !(*issue)) {
            (*issue) = true;
            return;
        }
        write(client->cli_fd, tmp, (strlen(tmp) - 1));
        write(client->cli_fd, "\r\n", 2);
        if (client->last_command_parsed)
            delete_list_arg(client->last_command_parsed);
        client->last_command_parsed = get_list_arg(tmp);
        free(tmp);
    }
}

static bool client_logic(client_t *client)
{
    fd_set rdfds;
    fd_set wrtfds;
    bool issue = false;

    if (!connect_to_server(client))
        return false;
    while (1) {
        set_fds(&wrtfds, &rdfds, client);
        if (!select(client->cli_fd + 1, &rdfds, &wrtfds, NULL, NULL))
            break;
        if (FD_ISSET(client->cli_fd, &rdfds))
            read_server(client, &issue);
        if (FD_ISSET(client->cli_fd, &wrtfds))
            uinput(client, &rdfds, &issue);
        if (issue)
            return true;
    }
    close(client->cli_fd);
    return true;
}

int main(int ac, char **av)
{
    client_t client;
    int ret = 0;

    client.last_command_parsed = NULL;
    ret = parse_client(ac, av, &client);
    if (ret != 0) {
        if (ret == 1)
            return 0;
        return ret;
    }
    if (!client_logic(&client))
        ret = 84;
    free(client.ip);
    if (client.last_command_parsed)
        delete_list_arg(client.last_command_parsed);
    return ret;
}
