/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#pragma once

#include "types.h"

bool init_server(server_t *myServ);
bool handle_server(server_t *myServ);
void accept_connection(server_t *myServ, fd_set *readfds,
    fd_set *writefds, int *max_fd);
