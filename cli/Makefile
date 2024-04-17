##
## EPITECH PROJECT, 2024
## MyTeams
## File description:
## Makefile
##

MAIN_FILE = src/main.c

MAIN_OBJ = $(MAIN_FILE:.c=.o)

SHARED_FILES = get_command.c \

SHARED_DIR = ../shared/
SHARED_SRC = $(addprefix $(SHARED_DIR), $(SHARED_FILES))
SHARED_OBJ = $(SHARED_SRC:.c=.o)

SRC_FILES =	parsing.c \
				read_flow.c \
				handle_response.c \

SRC_DIR = src/
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
INC = -I./include -I../shared/include \
	-I../libs/myteams/ -L ../libs/myteams/ -lmyteams

NAME = myteams_cli

CC = gcc

all: $(NAME)

$(NAME): $(OBJ) $(MAIN_OBJ) $(SHARED_OBJ)
	$(CC) -o $(NAME) $(SHARED_OBJ) $(OBJ) $(MAIN_OBJ) $(CFLAGS) $(INC)

run: all
	./$(NAME)

clean:
	rm -f $(OBJ) $(MAIN_OBJ) $(SHARED_OBJ) \
		$(TEST_OBJ) $(TEST_GCNO) $(TEST_GCDA)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

%.o: %.c
	$(CC) -c -o $@ $< $(CFLAGS) $(INC)
