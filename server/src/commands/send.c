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
#include "lists.h"

#include <string.h>

static void send_message(client_t *client, server_t *myServ)
{
    ptc_send(MESSAGE_SEND, "Message send.", client->_fd, &myServ->writefds);
}

static void send_message_to_receiver(char *msg, server_t *myServ,
    user_t *user_to_send)
{
    client_t *tmp = myServ->_list_client->first;

    while (tmp) {
        if (tmp->_user_data &&
            strcmp(tmp->_user_data->uuid, user_to_send->uuid) == 0)
            ptc_send(MESSAGE_RECIEVE, msg, tmp->_fd, &myServ->writefds);
        tmp = tmp->_next;
    }
}

static void save_message(user_t *user1, user_t *user2, char *msg)
{
    message_t *message = create_messages(user1->messages, user2->uuid,
        user1->uuid, msg);

    if (!message)
        return;
    add_to_list_messages(user2->messages, message);
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
    save_message(client->_user_data, user_to_send, command[2]);
    send_message(client, myServ);
    send_message_to_receiver(command[2], myServ, user_to_send);
}
