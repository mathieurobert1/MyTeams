/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list
*/

#include "types.h"
#include "utils.h"  // *
#include "commands.h"   // use_command_e

static channel_list_t *get_channel_list(char *team_uuid, server_t *myServ)
{
    team_t *team = team_get_by_uuid(team_uuid, myServ->_list_teams);

    if (!team)
        return NULL;
    return team->channels;
}

void list_command(char **command, server_t *myServ, client_t *client)
{
    char *str = NULL;
    channel_list_t *channels = NULL;

    if (!is_command_correct(command, 0, client))
        return;
    if (client->_use_state == EMPTY) {
        str = get_str_list_all_teams(myServ->_list_teams);
    } if (client->_use_state == TEAM) {
        channels = get_channel_list(client->_use_uuid_team, myServ);
        str = get_str_list_all_channels(channels);
    }
}
