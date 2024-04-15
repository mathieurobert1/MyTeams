/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** types
*/

#pragma once

#include <arpa/inet.h>
#include <stdbool.h>
#include <sys/select.h>

#define MAX_NAME_LENGTH 32
#define MAX_DESCRIPTION_LENGTH 255
#define MAX_BODY_LENGTH 512

typedef struct server_s {
    int _domain;
    int _type;
    int _protocol;
    int _fd;
    int _port;
    struct sockaddr_in _addr;
    struct client_list_s *_list_client;
    struct user_list_s *_list_users;
    struct team_list_s *_list_teams;
    fd_set readfds;
    fd_set writefds;
} server_t;

typedef struct client_s {
    int _fd;
    int _use_state;
    char *_use_uuid_team;
    char *_use_uuid_channel;
    char *_use_uuid_thread;
    struct user_s *_user_data;
    struct client_s *_next;
    struct client_s *_last;
} client_t;

typedef struct client_list_s {
    client_t *first;
    client_t *last;
    int nb_client;
} client_list_t;

#pragma pack(push, 1)
typedef struct message_s {
    char *sender_uuid;
    char *receiver_uuid;
    char *message;
    struct message_s *next;
    struct message_s *last;
} message_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct message_list_s {
    message_t *first;
    message_t *last;
    int nb_messages;
} message_list_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct user_s {
    char *uuid;
    char *username;
    message_list_t *messages;
    struct user_s *next;
    struct user_s *last;
} user_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct user_list_s {
    user_t *first;
    user_t *last;
    int nb_user;
} user_list_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct comment_s {
    char *uuid;
    char *content;
    char *author_uuid;
    time_t timestamp;
    struct comment_s *next;
    struct comment_s *last;
} comment_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct comment_list_s {
    comment_t *first;
    comment_t *last;
    int nb_comment;
} comment_list_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct thread_s {
    char *uuid;
    user_t *author;
    char *title;
    char *content;
    comment_list_t *comments;
    time_t timestamp;
    struct thread_s *next;
    struct thread_s *last;
} thread_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct thread_list_s {
    thread_t *first;
    thread_t *last;
    int nb_thread;
} thread_list_t;

#pragma pack(push, 1)
typedef struct channel_s {
    char *uuid;
    char *name;
    char *description;
    struct thread_list_s *threads;
    struct channel_s *next;
    struct channel_s *last;
} channel_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct channel_list_s {
    channel_t *first;
    channel_t *last;
    int nb_channel;
} channel_list_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct team_s {
    char *uuid;
    char *name;
    char *description;
    struct channel_list_s *channels;
    struct user_list_s *users;
    struct team_s *next;
    struct team_s *last;
} team_t;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct team_list_s {
    team_t *first;
    team_t *last;
    int nb_team;
} team_list_t;
#pragma pack(pop)

typedef struct command_s {
    char *_name;
    void (*_fct)(char **command, server_t *myServ, client_t *client);
} command_t;

extern const command_t _list_command[];
