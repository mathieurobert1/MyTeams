/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** delete_server
*/

#include "types.h"
#include "list_chained.h"

#include <stdlib.h>

void delete_server(server_t *myServ)
{
    if (!myServ)
        return;
    delete_clients(myServ->_list_client);
    free(myServ);
}
