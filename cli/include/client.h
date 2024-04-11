/*
** EPITECH PROJECT, 2024
** client
** File description:
** header file
*/
#pragma once
#include <stdbool.h>
#include <sys/select.h>

/**
 * @brief The client's structure containing key data
 *
 */
typedef struct client_s {
    int port;
    char *ip;
    int serv_fd;
    char **last_command_parsed;
    char *user_uuid;
    char *user_name;
} client_t;

/**
 * @brief Parse ac & av, filling client object.
 *
 * @param ac
 * @param av
 * @param client
 * @return int
 */
int parse_client(int ac, char **av, client_t *client);

/**
 * @brief Function used to read everything in a FD until \r\n
 *
 * @param fd
 * @param rn
 * @return char*
 */
char *read_flow(int fd, bool rn);

/**
 * @brief handle the server's response to execute the adequate function.
 *
 * @param client
 * @param msg
 */
void handle_response(client_t *client, char *msg);

/**
 * @brief function handling user input in case we can write into server.
 *
 * @param client
 * @param rdfds
 * @param issue
 */
void uinput(client_t *client, fd_set *rdfds, bool *issue);

/**
 * @brief if data to read from server, it reads & trigger handle_response.
 *
 * @param client
 * @param issue
 */
void read_server(client_t *client, bool *issue);
