/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** handle_commands
*/

#include "types.h"
#include "commands.h"
#include "protocol.h"
#include "shared.h"
#include "data.h"

#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static bool can_perform_command(client_t *client, char *command,
    server_t *myServ)
{
    if (strcmp(command, "/login") != 0) {
        if (client->_user_data)
            return true;
        else {
            ptc_send(CLIENT_ERROR_UNAUTHORIZED, "",
            client->_fd, &myServ->writefds);
            return false;
        }
    }
    return true;
}

static bool execute_command(int index, char **list_arg,
    server_t *myServ, client_t *client)
{
    if (strcmp(_list_command[index]._name, list_arg[0]) == 0) {
        if (!can_perform_command(client, _list_command[index]._name, myServ))
            return true;
        _list_command[index]._fct(list_arg, myServ, client);
        delete_list_arg(list_arg);
        data_save(myServ);
        return true;
    }
    return false;
}

static void handle_command(char *buffer, server_t *myServ, client_t *client)
{
    char **list_arg;

    if (!buffer)
        return;
    list_arg = get_list_arg(buffer);
    if (!list_arg) {
        ptc_send(SYNTAX_ERROR, "Error Syntax", client->_fd, &myServ->writefds);
        return;
    }
    for (int i = 0; _list_command[i]._name != NULL; i++) {
        if (execute_command(i, list_arg, myServ, client)) {
            free(buffer);
            return;
        }
    }
    ptc_send(SYNTAX_ERROR, "Error Syntax.", client->_fd, &myServ->writefds);
    free(buffer);
    delete_list_arg(list_arg);
}

void handle_client_commands(server_t *myServ)
{
    char *cmd = NULL;
    client_t *tmp = myServ->_list_client->first;
    client_t *tmp2 = myServ->_list_client->first;

    while (tmp != NULL) {
        tmp2 = tmp->_next;
        if (FD_ISSET(tmp->_fd, &myServ->readfds)) {
            cmd = read_data_client(tmp);
            handle_command(cmd, myServ, tmp);
        }
        tmp = tmp2;
    }
}
