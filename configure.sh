#!/bin/bash

if [ -f "/bin/apt-get" ]; then
    sudo apt-get update
    sudo apt-get install libsdl2-dev libpng-dev build-essential cmake
elif [ -f "/bin/pacman" ]; then
    sudo pacman -S sdl2 libpng base-devel cmake
fi

USER_OXU_CONFIG_DIR=/home/$USER/.config/oxu

mkdir $USER_OXU_CONFIG_DIR $USER_OXU_CONFIG_DIR/songs $USER_OXU_CONFIG_DIR/skins
cp -r res/ $USER_OXU_CONFIG_DIR/res/
