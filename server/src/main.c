/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** main
*/

#include <stdlib.h>

#include "types.h"
#include "parsing.h"
#include "server.h"

int main(int argc, char **argv)
{
    server_t *myServ = malloc(sizeof(server_t));
    int ret = 0;

    if (!myServ)
        return 84;
    if (!parse_command(argc, argv, myServ))
        ret = 84;
    else {
        if (!handle_server(myServ))
            ret = 84;
    }
    free(myServ);
    return ret;
}
