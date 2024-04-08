/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** list_chained
*/

#pragma once

#include "types.h"

// CLIENT //

/**
 * @brief add a client to a list
 *
 * @param list chained list
 * @param new_client client to add
 */
void add_to_list(client_list_t *list, client_t *new_client);

/**
 * @brief Create a client object in the list
 *
 * @param fd of the client
 * @param myServ server structure
 */
void create_client(int fd, server_t *myServ);

/**
 * @brief delete the clients list
 *
 * @param list to be deleted
 */
void delete_clients(client_list_t *list);

/**
 * @brief delete a given client
 *
 * @param client client to delete
 * @param myServ server structure
 */
void delete_a_client(client_t *client, server_t *myServ);

// CHANNELS //

/**
 * @brief initialize the channels list
 *
 * @return channel_list_t* 
 */
channel_list_t *init_list_channels(void);

/**
 * @brief delete the channels list
 *
 * @param list_channels list to delete
 */
void delete_list_channels(channel_list_t *list_channels);

/**
 * @brief Create a channel object
 * 
 * @param list_channels list to add to
 * @param name of the channel
 * @param uuid of the channel
 * @return channel_t*
 */
channel_t *create_channel(channel_list_t *list_channels, char *name, char *uuid);

/**
 * @brief delete a channel
 *
 * @param channel to delete
 */
void delete_channel(channel_t *channel);

/**
 * @brief add a channel to a channel list
 *
 * @param list to add to
 * @param channel to add
 */
void add_to_list_channel(channel_list_t *list, channel_t *channel);

// TEAMS //

/**
 * @brief initialize the teams list
 *
 * @return team_list_t* 
 */
team_list_t *init_list_teams(void);

/**
 * @brief delete the teams list
 *
 * @param list_teams to delete
 */
void delete_list_teams(team_list_t *list_teams);

/**
 * @brief Create a team object
 *
 * @param list_teams to add to
 * @param uuid of the team
 * @param name of the team
 * @return team_t* 
 */
team_t *create_team(team_list_t *list_teams, char *uuid, char *name);

/**
 * @brief delete a team
 *
 * @param team to delete 
 */
void delete_team(team_t *team);

/**
 * @brief add a team to a team list
 *
 * @param list to add to
 * @param team to add
 */
void add_to_list_team(team_list_t *list, team_t *team);

// THREADS //

/**
 * @brief initialize the threads list
 *
 * @return thread_list_t* 
 */
thread_list_t *init_list_threads(void);

/**
 * @brief delete the list of threads
 *
 * @param list_threads to delete
 */
void delete_list_threads(thread_list_t *list_threads);

/**
 * @brief Create a thread object
 *
 * @param list_threads to add to
 * @param uuid of the thread
 * @param title of the thread
 * @return thread_t* 
 */
thread_t *create_thread(thread_list_t *list_threads, char *uuid, char *title);

/**
 * @brief delete a thread
 *
 * @param thread to delete
 */
void delete_thread(thread_t *thread);

/**
 * @brief add a thread to a thread list
 *
 * @param list to add to
 * @param thread to add
 */
void add_to_list_threads(thread_list_t *list, thread_t *thread);

// USERS //

/**
 * @brief initialize the users list
 *
 * @return user_list_t* 
 */
user_list_t *init_list_users(void);

/**
 * @brief delete the users list
 *
 * @param list_users to delete
 */
void delete_list_users(user_list_t *list_users);

/**
 * @brief Create a user object
 *
 * @param list_users to add to
 * @param uuid of the user
 * @param user_name of the user
 * @return user_t* 
 */
user_t *create_user(user_list_t *list_users, char *uuid, char *user_name);

/**
 * @brief delete the user
 *
 * @param user to delete
 */
void delete_user(user_t *user);

/**
 * @brief add a user to a user list
 *
 * @param list to add to
 * @param user to add
 */
void add_to_list_users(user_list_t *list, user_t *user);