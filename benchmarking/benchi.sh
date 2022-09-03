#!/usr/bin/bc
#cd bin
gnome-terminal -e "bash -c 'top | grep probe'" &
gnome-terminal -e "bash -c 'top | grep analyze'" &
gnome-terminal -e "bash -c 'top | grep responses'" &
