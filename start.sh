export LD_LIBRARY_PATH=$(pwd)/libs/myteams:$LD_LIBRARY_PATH
make re
valgrind --leak-check=full ./myteams_cli localhost 8888 