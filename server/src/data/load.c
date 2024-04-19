/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** load
*/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "types.h"
#include "data.h"

bool check_fd(int fd)
{
    fd_set readfds;

    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    if (select(fd + 1, &readfds, NULL, NULL, NULL) == -1) {
        write(1, "Error with select in data_save\n", 32);
        return false;
    }
    if (!FD_ISSET(fd, &readfds))
        return false;
    return true;
}

server_t *data_load(void)
{
    int fd = open("server.db", O_RDONLY | O_CREAT, 0666);
    server_t *server = NULL;

    if (fd == -1) {
        write(1, "Error with open in data_save\n", 30);
        return NULL;
    }
    if (!check_fd(fd)) {
        write(1, "Error with check_fd in data_save\n", 33);
        return NULL;
    }
    server = deserialize_server(fd);
    if (server == NULL) {
        write(1, "Error with malloc in data_load\n", 32);
        return NULL;
    }
    return server;
}
