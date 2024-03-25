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

static void run_server(server_t *myServ)
{
    fd_set readfds = {0};
    fd_set writefds = {0};
    int max_fd;
    int activity;

    while (1) {
        // accept_connection(myServ, &readfds, &writefds, &max_fd);
        FD_ZERO(&readfds);
        FD_SET(myServ->_fd, &readfds);
        FD_ZERO(&writefds);
        max_fd = myServ->_fd;
        //set_fd_client(&max_fd, myServ, &readfds, &writefds);
        activity = select(max_fd + 1, &readfds, &writefds, NULL, NULL);
        if ((activity < 0)) {
            continue;
        }
        //handle_client_commands(myServ, &readfds);
    }
}

bool handle_server(server_t *myServ)
{
    if (!init_server(myServ))
        return false;
    run_server(myServ);
    return true;
}
