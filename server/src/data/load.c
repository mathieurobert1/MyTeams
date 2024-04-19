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

server_t *data_load(void)
{
    int fd = open("server.db", O_RDONLY | O_CREAT, 0666);
    server_t *server = NULL;
    fd_set readfds;

    if (fd == -1) {
        write(1, "Error with open in data_save\n", 30);
        return NULL;
    }
    FD_ZERO(&readfds);
    FD_SET(fd, &readfds);
    if (select(fd + 1, &readfds, NULL, NULL, NULL) == -1) {
        write(1, "Error with select in data_save\n", 32);
        return NULL;
    }
    if (!FD_ISSET(fd, &readfds))
        return NULL;
    server = deserialize_server(fd);
    if (server == NULL) {
        write(1, "Error with malloc in data_load\n", 32);
        return NULL;
    }
    return server;
}
