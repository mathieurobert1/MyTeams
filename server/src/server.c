/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#include "types.h"
#include "server.h"
#include <sys/select.h>
#include <unistd.h>
#include "commands.h"

static void set_fd_client(int *max_fd, server_t *myServ)
{
    client_t *tmp = myServ->_list_client->first;

    while (tmp != NULL) {
        FD_SET(tmp->_fd, &myServ->readfds);
        FD_SET(tmp->_fd, &myServ->writefds);
        if (tmp->_fd > *max_fd) {
            *max_fd = tmp->_fd;
        }
        tmp = tmp->_next;
    }
}

static void run_server(server_t *myServ)
{
    int max_fd;
    int activity;

    while (1) {
        accept_connection(myServ, &max_fd);
        FD_ZERO(&myServ->readfds);
        FD_SET(myServ->_fd, &myServ->readfds);
        FD_ZERO(&myServ->writefds);
        max_fd = myServ->_fd;
        set_fd_client(&max_fd, myServ);
        activity = select(max_fd + 1, &myServ->readfds, &myServ->writefds, NULL, NULL);
        if ((activity < 0)) {
            continue;
        }
        handle_client_commands(myServ);
    }
}

bool handle_server(server_t *myServ)
{
    if (!init_server(myServ))
        return false;
    run_server(myServ);
    return true;
}
