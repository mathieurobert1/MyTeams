/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** send
*/

#include "types.h"
#include "protocol.h"
#include "utils.h"
#include "logging_server.h"

#include <string.h>

static void send_message(client_t *client, server_t *myServ)
{
    ptc_send(MESSAGE_SEND, "Message send.", client->_fd, &myServ->writefds);
    //save
}

static void receive_message(char *msg, server_t *myServ, user_t *user_to_send)
{
    client_t *tmp = myServ->_list_client->first;

    while (tmp) {
        if (tmp->_user_data &&
            strcmp(tmp->_user_data->uuid, user_to_send->uuid) == 0)
            ptc_send(MESSAGE_RECIEVE, msg, tmp->_fd, &myServ->writefds);
        tmp = tmp->_next;
    }
    //save
}

void send_command(char **command, server_t *myServ, client_t *client)
{
    user_t *user_to_send = NULL;

    if (!is_correct_command(&myServ->writefds, command, 2, client->_fd))
        return;
    if (strlen(command[2]) > MAX_BODY_LENGTH) {
        ptc_send(ERROR_PARAMETERS, "Body length too long.",
        client->_fd, &myServ->writefds);
        return;
    }
    user_to_send = get_user_by_uuid(command[1], myServ);
    if (!user_to_send) {
        ptc_send(ERROR_PARAMETERS, "User uuid didn't exist on domain.",
        client->_fd, &myServ->writefds);
        return;
    }
    server_event_private_message_sended(client->_user_data->uuid,
    user_to_send->uuid, command[2]);
    send_message(client, myServ);
    receive_message(command[2], myServ, user_to_send);
}
