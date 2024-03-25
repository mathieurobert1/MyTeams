/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** accept_connection
*/

#include "types.h"
#include <sys/select.h>

static void accept_connection(server_t *myServ, fd_set *readfds,
    fd_set *writefds, int *max_fd)
{
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    int new_socket;

    if (FD_ISSET(myServ->_fd, readfds)) {
        new_socket = accept(myServ->_fd, (struct sockaddr*)&cliaddr,
        (socklen_t *)&len);
        if (new_socket < 0) {
            perror("accept failed");
            return;
        }
        write(new_socket, "220 Service ready for new user.\r\n", 33);
        create_client(new_socket, myServ);
        FD_SET(new_socket, readfds);
        FD_SET(new_socket, writefds);
        if (new_socket > *max_fd) {
            *max_fd = new_socket;
        }
    }
}
