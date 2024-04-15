/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_command
*/

#pragma once

#include "types.h"

/**
 * @brief prints the channels list
 *
 * @param server server structure of the program
 * @param client client's caller
 */
void print_channels(server_t *server, client_t *client);

/**
 * @brief prints the threads list
 *
 * @param server server structure of the program
 * @param client client's caller
 */
void print_threads(server_t *server, client_t *client);

/**
 * @brief prints the comments list
 *
 * @param server server structure of the program
 * @param client client's caller
 */
void print_replys(server_t *server, client_t *client);
