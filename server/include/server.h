/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#pragma once

#include "types.h"

/**
 * @brief initialize the server
 *
 * @param myServ server structure
 * @return true the server is created
 * @return false instead
 */
bool init_server(server_t *myServ);

/**
 * @brief launch the server
 *
 * @param myServ server structure
 * @return true all is fine
 * @return false there is an error during loop server
 */
bool handle_server(server_t *myServ);

/**
 * @brief accept clients who wants to connect
 *
 * @param myServ server structure
 * @param max_fd fd max in the select function
 */
void accept_connection(server_t *myServ, int *max_fd);

/**
 * @brief delete the server struct
 *
 * @param myServ server structure
 */
void delete_server(server_t *myServ);
