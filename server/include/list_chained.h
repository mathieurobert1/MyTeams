/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_chained
*/

#pragma once

#include "types.h"

/// @brief add a client to a list
/// @param list chained list
/// @param new_client client to add
void add_to_list(client_list_t *list, client_t *new_client);

/// @brief create a client with his fd
/// @param fd of the client
/// @param myServ server structure
void create_client(int fd, server_t *myServ);

/// @brief delete the clients list
/// @param list to be deleted
void delete_clients(client_list_t *list);

/// @brief delete a given client
/// @param client client to delete
/// @param myServ server structure
void delete_a_client(client_t *client, server_t *myServ);
