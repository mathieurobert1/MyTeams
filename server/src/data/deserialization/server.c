/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#include "types.h"  // server_t
#include "data.h"   // deserialize_user_list, deserialize_team_list

#include <unistd.h> // read
#include <stdlib.h> // malloc

server_t *deserialize_server(int fd)
{
    server_t *server = malloc(sizeof(server_t));

    read(fd, server, sizeof(server_t));
    server->_list_users = deserialize_user_list(fd);
    server->_list_teams = deserialize_team_list(fd);
    return server;
}
