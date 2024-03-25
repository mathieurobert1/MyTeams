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
} server_t;
