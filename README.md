# oXu
oXu is a rhythm game inspired by the osu! project.
The game is still in an alpha state and under heavy development.
Currently the game is available on Windows and Linux and needs to be compiled from source.

# Compilation
  - g++ Main.cpp oxuCore/game.cpp oxuGameHandlers/graphicsHandler.cpp oxuGameHandlers/hitObjectManager.cpp oxuGameHandlers/inputHandler.cpp oxuGameHandlers/mapManager.cpp oxuGameHandlers/soundHandler.cpp oxuGameComponents/approachCircle.cpp oxuGameComponents/hitCircle.cpp oxuGameComponents/mapSelectButton.cpp oxuGameComponents/playField.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lbass -lpthread -lboost_system -lboost_filesystem -o /root/Documents/oXu/src/output.o

