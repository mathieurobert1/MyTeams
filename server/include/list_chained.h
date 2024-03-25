/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_chained
*/

#pragma once

#include "types.h"

void add_to_list(client_list_t *list, client_t *new_client);
void create_client(int fd, server_t *myServ);
void delete_clients(client_list_t *list);
void delete_a_client(client_t *client, server_t *myServ);
