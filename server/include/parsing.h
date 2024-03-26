/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** parsing
*/

#pragma once

#include <stdbool.h>
#include "types.h"

/**
 * @brief parse the command line
 *
 * @param argc nb of arguments
 * @param argv tab of arguments
 * @param myServ server structure
 * @return true the parsing is fine
 * @return false instead
 */
bool parse_command(int argc, char **argv, server_t *myServ);
