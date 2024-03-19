##
## EPITECH PROJECT, 2024
## MyTeams
## File description:
## Makefile of the project
##

SERVER_PATH = server/
CLI_PATH = cli/

SERVER_BIN = myteams_server
CLI_BIN = myteams_cli

all:
	$(MAKE) -C server
	$(MAKE) -C cli
	cp $(SERVER_PATH)$(SERVER_BIN) .
	cp $(CLI_PATH)$(CLI_BIN) .

clean:
	$(MAKE) clean -C server
	$(MAKE) clean -C cli

fclean:
	$(MAKE) fclean -C server
	$(MAKE) fclean -C cli
	rm -f $(SERVER_BIN) $(CLI_BIN)

run_tests:
	$(MAKE) tests_run -C server
	$(MAKE) tests_run -C cli

re: fclean all
