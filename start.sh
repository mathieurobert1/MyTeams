export LD_LIBRARY_PATH=$(pwd)/libs/myteams:$LD_LIBRARY_PATH
make re
./myteams_cli localhost 8888 