/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** commands
*/

#pragma once

#include <stddef.h> // for NULL

#include "types.h"  // for server_t, client_t and command_t

enum use_command_e {
    NONE = 0,
    EMPTY = 1,
    TEAM = 2,
    CHANNEL = 3,
    THREAD = 4
};

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

// Utils Command /use //

/**
 * @brief change the use state
 *
 * @param use_state use state
 * @param uuid of use
 * @param client to change state
 */
void change_use(int use_state, char *uuid, client_t *client);

/**
 * @brief check if uuid correspond to team/channel/thread
 *
 * @param uuid to find
 * @param myServ server_t struct
 * @param client
 * @return true
 * @return false
 */
bool uuid_is_team(char **command, server_t *myServ, client_t *client);

// Utils Command /subscribed //

/**
 * @brief Get the message list users in form of [...(user1), ...(user2), ...]
 *
 * @param list_users
 * @return char*
 */
char *get_message_list_users(user_list_t *list_users);

/**
 * @brief Get the message list team in form of [...(team1), ...(team2), ...]
 * The fonction check if the user is subscribed to the team
 *
 * @param list_teams initial list of teams
 * @param user user to check
 * @return char*
 */
char *get_message_list_team(team_list_t *list_teams, user_t *user);
