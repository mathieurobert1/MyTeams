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
#include "data.h"

int main(int argc, char **argv)
{
    server_t *myServ = data_load();
    int ret = 0;

    if (!myServ)
        return 84;
    if (!parse_command(argc, argv, myServ))
        ret = 84;
    else {
        if (!handle_server(myServ))
            ret = 84;
    }
    delete_server(myServ);
    return ret;
}
