/*
** EPITECH PROJECT, 2024
** myftp
** File description:
** init server
*/

#include "types.h"
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>

static bool set_socket(server_t *myServ)
{
    struct protoent *protocol = getprotobyname("TCP");

    myServ->_domain = AF_INET;
    myServ->_type = SOCK_STREAM;
    myServ->_protocol = protocol->p_proto;
    myServ->_fd = socket(myServ->_domain, myServ->_type, myServ->_protocol);
    if (myServ->_fd < 0) {
        perror("socket failed");
        return false;
    }
    return true;
}

static bool set_bind(server_t *myServ)
{
    myServ->_addr.sin_family = myServ->_domain;
    myServ->_addr.sin_port = htons(myServ->_port);
    myServ->_addr.sin_addr.s_addr = htons(INADDR_ANY);
    if (setsockopt(myServ->_fd, SOL_SOCKET, SO_REUSEADDR,
        &(int){1}, sizeof(int)) < 0) {
        perror("reuse port failed");
        return false;
    }
    if (bind(myServ->_fd, (struct sockaddr *)&myServ->_addr,
        sizeof(myServ->_addr)) != 0) {
        perror("bind failed");
        return false;
    }
    return true;
}

static bool set_listen(server_t *myServ)
{
    if (listen(myServ->_fd, 10) != 0) {
        perror("listen failed");
        return false;
    }
    return true;
}

static bool set_list_client(server_t *myServ)
{
    (void) myServ;
    return true;
}

bool init_server(server_t *myServ)
{
    if (!set_socket(myServ) ||
        !set_bind(myServ) ||
        !set_listen(myServ) ||
        !set_list_client(myServ))
        return false;
    return true;
}
