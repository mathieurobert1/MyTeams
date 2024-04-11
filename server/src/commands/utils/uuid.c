/*
** EPITECH PROJECT, 2024
** MyTeams
** File description:
** uuid
*/

#include <uuid/uuid.h>
#include <stddef.h>

char *create_uuid(void)
{
    uuid_t binuuid;
    char *uuid = malloc(37);

    if (!uuid)
        return NULL;
    uuid_generate_random(binuuid);
    uuid_unparse_lower(binuuid, uuid);
    return uuid;
}
