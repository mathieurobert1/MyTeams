/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#include "types.h"  // server_t
#include "data.h"   // serialize_user_list, serialize_team_list

#include <unistd.h> // write

void serialize_server(int fd, server_t *server)
{
    write(fd, server, sizeof(server_t));
    serialize_user_list(fd, server->_list_users);
    serialize_team_list(fd, server->_list_teams);
}
