/*
** EPITECH PROJECT, 2024
** client
** File description:
** header file
*/
#pragma once
#include <stdbool.h>

typedef struct client_s {
    int port;
    char *ip;
    int cli_fd;
    char **last_command_parsed;
} client_t;

int parse_client(int ac, char **av, client_t *client);
char *read_flow(int fd, bool rn);
void handle_response(client_t *client, char *msg);