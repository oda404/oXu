# oXu!
oXu! is an osu! client written in C++. The project is made mainly as a learning excersise.
oXu! is still in a pre-alpha state and under heavy development.

## Features
The game is missing a lot of features that are standard in osu!, so don't expect it to be playable.

## Playing oXu!
<b>Keep in mind that the game was only tested on Linux.</b><br>
```console
git clone --recursive https://github.com/oda404/oXu
cd oXu
sudo ./deps.sh
make
```
The -j# flag can used to speed up the build process. Where # is the number of threads used to make.<br>
A new file named oXu will pop up, which you can execute using ./oXu.<br>
Before trying to play oXu you should add some beatmaps to the songs folder(oXu! supports osu! beatmaps).

## Dev info
- The game uses SDL2 for graphics and events, and SDL_Mixer for the sound.
- To clean the build tree of oXu! specific compiled objs do: make clean
- To clean the build tree completely (including 3rdParty compiled objs) do: make clean-all

### 3rd Party libs
- The game uses spdlog for the logging system.
