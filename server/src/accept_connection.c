/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** accept_connection
*/

#include "types.h"
#include "list_chained.h"
#include <sys/select.h>

#include <unistd.h>

void accept_connection(server_t *myServ, int *max_fd)
{
    struct sockaddr_in cliaddr;
    int len = sizeof(cliaddr);
    int new_socket;

    if (FD_ISSET(myServ->_fd, &myServ->readfds)) {
        new_socket = accept(myServ->_fd, (struct sockaddr*)&cliaddr,
        (socklen_t *)&len);
        if (new_socket < 0) {
            return;
        }
        create_client(new_socket, myServ);
        FD_SET(new_socket, &myServ->readfds);
        FD_SET(new_socket, &myServ->writefds);
        if (new_socket > *max_fd) {
            *max_fd = new_socket;
        }
    }
}
