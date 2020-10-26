#!/bin/bash

LIST=$(docker ps -a -q)
if [ ! -z "$LIST" ]; then
    echo "Remove containers $LIST..."
    docker rm -f $LIST
fi

LIST=$(docker images  | grep "^<none>" | awk '{print $3}')
if [ ! -z "$LIST" ]; then
    echo "Remove images $LIST..."
    docker rmi -f $LIST
    echo "Warning: named images was not deleted"
fi
