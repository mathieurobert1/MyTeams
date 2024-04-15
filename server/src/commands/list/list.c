/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list
*/

#include "types.h"
#include "utils.h"  // *
#include "commands.h"   // use_command_e
#include "list_command.h"   // *


static void list_print(client_t *client, server_t *myServ)
{
    if (client->_use_state == EMPTY)
        print_list_all_teams(myServ->_list_teams, client->_fd,
            &myServ->writefds);
    if (client->_use_state == TEAM)
        print_channels(myServ, client);
    if (client->_use_state == CHANNEL)
        print_threads(myServ, client);
    if (client->_use_state == THREAD)
        print_replys(myServ, client);
}

void list_command(char **command, server_t *myServ, client_t *client)
{
    if (!is_correct_command(&myServ->writefds, command, 0, client->_fd))
        return;
    if (!is_context_def(client->_fd, &myServ->writefds, client->_use_state))
        return;
    list_print(client, myServ);
}
