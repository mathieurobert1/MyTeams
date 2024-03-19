##
## EPITECH PROJECT, 2024
## MyTeams
## File description:
## Makefile of the project
##

all:
	$(MAKE) -C server
	$(MAKE) -C cli

clean:
	$(MAKE) clean -C server
	$(MAKE) clean -C cli

fclean:
	$(MAKE) fclean -C server
	$(MAKE) fclean -C cli

tests_run:
	$(MAKE) tests_run -C server
	$(MAKE) tests_run -C cli

re: fclean all
