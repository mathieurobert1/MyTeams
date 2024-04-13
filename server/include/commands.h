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

//Utils Command /create //

/**
 * @brief Create a new team object
 *
 * @param command array
 * @param myServ server_t struct
 * @param client client_t struct
 */
void create_new_team(char **command, server_t *myServ, client_t *client);

/**
 * @brief Create a new channel object
 *
 * @param command array
 * @param myServ server_t struct
 * @param client client_t struct
 */
void create_new_channel(char **command, server_t *myServ, client_t *client);

/**
 * @brief Get the message object
 *
 * @param team_uuid char *
 * @param team_name char *
 * @param team_description char *
 * @param code char *
 * @return char*
 */
char *get_message_create(char *team_uuid, char *team_name,
    char *team_description, char *code);

/**
 * @brief is_no_error in arguments
 *
 * @param command array
 * @param myServ server_t struct
 * @param client client_t struct
 * @param length of the second argument
 * @return true
 * @return false
 */
bool is_no_error(char **command, server_t *myServ, client_t *client,
    size_t length);

/**
 * @brief send messages to clients in team
 *
 * @param client client_t struct
 * @param myServ server_t struct
 * @param msg_all message to send
 */
void find_clients_to_send(client_t *client, server_t *myServ, char *msg_all);

/**
 * @brief send messages clients in team
 *
 * @param user user related to clisent
 * @param tmp client_t struct
 * @param myServ server_t struct
 * @param msg_all message to send
 */
void find_user_to_send(user_t *user, client_t *tmp,
    server_t *myServ, char *msg_all);

/**
 * @brief Create a new thread object
 *
 * @param command array
 * @param myServ server_t struct
 * @param client client_t struct
 */
void create_new_thread(char **command, server_t *myServ, client_t *client);

/**
 * @brief Create a new reply object
 *
 * @param command array
 * @param myServ server_t struct
 * @param client client_t struct
 */
void create_new_reply(char **command, server_t *myServ, client_t *client);
