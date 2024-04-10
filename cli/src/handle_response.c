/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** handle_response
*/
#include "client.h"
#include "shared.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "logging_client.h"
#include "protocol.h"

void handle_response(client_t *client, char *msg) 
{
    char **parsed = get_list_arg(msg);
    int code = atoi(parsed[0]);

    if (code == 214)
        write(1, msg, strlen(msg));
    if (code == LOGGED_OUT)
        client_event_logged_out(parsed[1], parsed[2]);
}
