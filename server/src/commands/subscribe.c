/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** subscribe
*/

#include "types.h"
#include "utils.h"
#include "protocol.h"
#include "lists.h"
#include "logging_server.h"

#include <unistd.h>

void subscribe_command(char **command, server_t *myServ, client_t *client)
{
    team_t *team = NULL;

    if (!is_correct_command(&myServ->writefds, command, 1, client->_fd))
        return;
    team = get_team_by_uuid(command[1], myServ);
    if (!team) {
        ptc_send(ERROR_PARAMETERS, "Team uuid didn't exist on domain.",
        client->_fd, &myServ->writefds);
        return;
    }
    add_to_list_users(team->users, client->_user_data);
    server_event_user_subscribed(command[1], client->_user_data->uuid);
    ptc_send(COMMAND_SUCCESS, "Command success.",
    client->_fd, &myServ->writefds);
}
