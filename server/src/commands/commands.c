/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** commands
*/

#include "types.h"
#include "commands.h"
#include <unistd.h>

const command_t _list_command[] = {
    {"/help", help_command},
    {"/login", login_command},
    {"/logout", logout_command},
    {"/users", users_command},
    {"/user", user_command},
    {"/send", send_command},
    {"/messages", messages_command},
    {"/subscribe", subscribe_command},
    {"/subscribed", subscribed_command},
    {"/unsubscribe", unsubscribe_command},
    {"/use", use_command},
    {"/create", create_command},
    {"/list", list_command},
    {"/info", info_command},
    {NULL, NULL}
};
