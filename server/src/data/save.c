/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** save
*/

#include <fcntl.h>
#include <unistd.h>

#include "types.h"
#include "data.h"

void data_save(server_t *server)
{
    int fd = open("server.db", O_CREAT | O_WRONLY | O_TRUNC, 0666);
    fd_set writefds;
    int result_select = 0;

    if (fd == -1) {
        write(1, "Error with open in data_save\n", 30);
    }
    FD_ZERO(&writefds);
    FD_SET(fd, &writefds);
    result_select = select(fd + 1, NULL, &writefds, NULL, NULL);
    if (result_select == -1) {
        write(1, "Error with select in data_save\n", 32);
    }
    if (FD_ISSET(fd, &writefds)) {
        serialize_server(fd, server);
    }
}
