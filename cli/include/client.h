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
} client_t;


int parse_client(int ac, char **av, client_t *client);