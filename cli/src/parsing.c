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

static void display_help() {
    printf("USAGE: ./myteams_cli ip port\n");
    printf("\tip\t is the server ip address on which the server socket listens\n");
    printf("\tport\t is the port number on which the server socket listens\n");
}

int parse_client(int ac, char **av, client_t *client)
{
    if (ac == 2 && strcmp(av[1], "-help") == 0) {
        display_help();
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
