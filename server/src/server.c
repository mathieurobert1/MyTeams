/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** server
*/

#include "types.h"
#include "server.h"

static void run_server(server_t *myServ)
{
    (void) myServ;
}

bool handle_server(server_t *myServ)
{
    if (!init_server(myServ))
        return false;
    run_server(myServ);
    return true;
}
