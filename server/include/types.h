/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** types
*/

#pragma once

#include <arpa/inet.h>
#include <stdbool.h>

typedef struct server_s {
    int _domain;
    int _type;
    int _protocol;
    int _fd;
    int _port;
    struct sockaddr_in _addr;
    struct client_list_s *_list_client;
} server_t;

typedef struct client_s {
    int _fd;
    struct client_s *_next;
    struct client_s *_last;
} client_t;

typedef struct client_list_s {
    client_t *first;
    client_t *last;
    int nb_client;
} client_list_t;
