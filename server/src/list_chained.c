/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** list
*/

#include "types.h"
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void add_to_list(client_list_t *list, client_t *new_client)
{
    client_t *tmp = list->first;

    if (list->nb_client == 0) {
        list->first = new_client;
        list->last = new_client;
        new_client->_last = NULL;
        new_client->_next = NULL;
        list->nb_client++;
        return;
    }
    list->first = new_client;
    new_client->_last = NULL;
    tmp->_last = new_client;
    new_client->_next = tmp;
    list->nb_client++;
}

void create_client(int fd, server_t *myServ)
{
    client_t *new_client = malloc(sizeof(client_t));

    if (!new_client)
        return;
    new_client->_fd = fd;
    new_client->_user_data = NULL;
    add_to_list(myServ->_list_client, new_client);
}

void delete_clients(client_list_t *list)
{
    client_t *tmp = list->first;
    client_t *next;

    while (tmp != NULL) {
        next = tmp->_next;
        free(tmp);
        tmp = next;
    }
    free(list);
}

static void free_client(client_t *client)
{
    close(client->_fd);
    free(client);
}

void delete_a_client(client_t *client, server_t *myServ)
{
    client_list_t *list = myServ->_list_client;

    if (client->_next)
        client->_next->_last = client->_last;
    if (client->_last)
        client->_last->_next = client->_next;
    if (list->first == client)
        list->first = client->_next;
    if (list->first)
        list->first->_last = NULL;
    if (list->last == client)
        list->last = client->_last;
    if (list->last)
        list->last->_next = NULL;
    list->nb_client--;
    free_client(client);
}
