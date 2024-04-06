/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** commands
*/

#pragma once

#include "types.h"

/**
 * @brief handle the client's commands
 *
 * @param myServ server structure
 */
void handle_client_commands(server_t *myServ);

/**
 * @brief read the client command
 *
 * @param tmp client to read
 * @return char* command of the client
 */
char *read_data_client(client_t *tmp);

/**
 * @brief Get the list of the client command
 *
 * @param buffer command in char*
 * @return char** list of char* command
 */
char **get_list_arg(char *buffer);

/**
 * @brief delete the command list
 *
 * @param list_arg command list
 */
void delete_list_arg(char **list_arg);

/**
 * @brief help_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void help_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief login_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void login_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief logout_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void logout_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief users_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void users_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief user_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void user_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief send_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void send_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief messages_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void messages_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief subscribe_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void subscribe_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief subscribed_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void subscribed_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief unsubscribe_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void unsubscribe_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief use_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void use_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief create_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void create_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief list_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void list_command(char **command, server_t *myServ, client_t *client);

/**
 * @brief info_command
 *
 * @param command array
 * @param myServ server structure
 * @param client client structure
 */
void info_command(char **command, server_t *myServ, client_t *client);