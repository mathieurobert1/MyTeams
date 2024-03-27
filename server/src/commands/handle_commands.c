/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** handle_commands
*/

#include "types.h"
#include "commands.h"

#include <stdlib.h>
#include <string.h>

#include <unistd.h>

static void handle_command(char *buffer, server_t *myServ, client_t *client)
{
    char **list_arg = get_list_arg(buffer);

    if (!list_arg) {
        //send error syntax
        write(client->_fd, "ERROR a a \n", 11);
        return;
    }
    for (int i = 0; _list_command[i]._name != NULL; i++) {
        if (strcmp(_list_command[i]._name, list_arg[0]) == 0) {
            _list_command[i]._fct(list_arg, myServ, client);
            delete_list_arg(list_arg);
            return;
        }
    }
    write(client->_fd, "ERROR\n", 6);
    //send error syntax
    delete_list_arg(list_arg);
}

void handle_client_commands(server_t *myServ)
{
    char *cmd;
    client_t *tmp = myServ->_list_client->first;
    client_t *tmp2 = myServ->_list_client->first;

    while (tmp != NULL) {
        tmp2 = tmp->_next;
        if (FD_ISSET(tmp->_fd, &myServ->readfds)) {
            cmd = read_data_client(tmp);
            handle_command(cmd, myServ, tmp);
            exit(0);
        }
        tmp = tmp2;
    }
}
