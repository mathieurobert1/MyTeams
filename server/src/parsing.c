/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** parsing
*/

#include "types.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

static void display_help(void)
{
    write(1, "USAGE: ./myteams_server port\n\t"
    "port is the port number on which the server socket listens.\n", 90);
}

static bool set_parsing_values(char **argv, server_t *myServ)
{
    myServ->_port = atoi(argv[1]);
    if (myServ->_port == 0) {
        write(2, "Error: wrong port number\n", 25);
        return false;
    }
    return true;
}

bool parse_command(int argc, char **argv, server_t *myServ)
{
    if (argc == 2) {
        if (strcmp("-help", argv[1]) == 0) {
            display_help();
            free(myServ);
            exit(0);
        }
        return set_parsing_values(argv, myServ);
    }
    write(2, "Error: wrong arguments\n", 23);
    return false;
}
