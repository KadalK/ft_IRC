#!/bin/zsh

make

PORT=6667
PASS=123
NB_CLIENTS=5
CHAN="#test"

./server/ircserv $PORT $PASS > serv.log 2>&1 &
SERVER_PID=$!

sleep 1

for i in $(seq 1 $NB_CLIENTS); do
    USERNAME="user$i"
    NICK="nick$i"

    gnome-terminal -- bash -c "
    (
        echo PASS $PASS
        sleep 0.5

        echo NICK $NICK
        sleep 0.5

        echo USER $USERNAME 0 '*' :$USERNAME
        sleep 1

        echo 'JOIN #test'
        sleep 0.5

        echo 'JOIN #test2'
        sleep 0.5

        echo 'PRIVMSG #test :salut'
        sleep 1

        echo \"TOPIC $CHAN $i\"
        sleep 1

        cat
    ) | nc -C 127.0.0.1 $PORT

    exec bash
    "
done