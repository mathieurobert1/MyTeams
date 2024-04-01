/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** main
*/
#include "client.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int parse_client(int ac, char **av, client_t *client)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        printf("on affiche l'aide");
        return 1;
    }
    if (ac != 3)
        return 84;
    client->ip = strdup(av[1]);
    client->port = atoi(av[2]);
    if (client->port == 0 || client->ip == NULL)
        return 84;
    return 0;
}
