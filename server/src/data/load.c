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
    int fd = open("server.db", O_RDONLY);
    server_t *server = NULL;

    if (fd == -1) {
        write(1, "Error with open in data_save\n", 30);
        return NULL;
    }
    server = deserialize_server(fd);
    if (server == NULL) {
        write(1, "Error with malloc in data_load\n", 32);
        return NULL;
    }
    return server;
}
