# oXu!
oXu! is a custom osu! client written in C++. The project is made mainly as a learning excersise.
oXu! is still in a pre-alpha state and under heavy development.

## Features
The game is missing a lot of features that are standard in osu!, so don't expect it to be playable.

## Playing oXu!
<b>Keep in mind that the game was only tested on Linux.</b><br>
```console
git clone --recursive https://github.com/oda404/oXu
cd oXu
sudo ./configure.sh
cd build
cmake ..
make -j#
```
Skins and beatmaps can be added into the /home/user/.config/oXu/

### 3rd Party libs
- SDL2
- SDL2_Mixer
- SDL2_TTF
- SDL2_Image
- spdlog
