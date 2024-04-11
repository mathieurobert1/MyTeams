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

    if (fd == -1) {
        write(1, "Error with open in data_save\n", 30);
    }
    serialize_server(fd, server);
}
