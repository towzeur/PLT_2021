#!/bin/bash

if [ -z "$1" ]; then
    echo "Utilisation:"
    echo "  $0 <nom du conteneur docker>"
    exit 2
fi
IMAGE=$1

docker exec -it \
    --user=$(id -u $USER) \
    $IMAGE \
    /bin/bash



