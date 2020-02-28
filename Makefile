
output: main.o game.o approachCircle.o hitCircle.o mapSelectButton.o playField.o graphicsHandler.o hitObjectManager.o inputHandler.o mapManager.o soundHandler.o
	g++ main.o game.o approachCircle.o hitCircle.o mapSelectButton.o playField.o graphicsHandler.o hitObjectManager.o inputHandler.o mapManager.o soundHandler.o -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lpthread -lboost_system -lboost_filesystem -L./3rdPartyDependencies -lbass -o oXu!
	rm *.o

main.o: src/main.cpp
	g++ -c  src/main.cpp

game.o: src/oxuCore/game.cpp
	g++ -c src/oxuCore/game.cpp

approachCircle.o: src/oxuGameComponents/approachCircle.cpp
	g++ -c src/oxuGameComponents/approachCircle.cpp

hitCircle.o: src/oxuGameComponents/hitCircle.cpp
	g++ -c src/oxuGameComponents/hitCircle.cpp

mapSelectButton.o: src/oxuGameComponents/mapSelectButton.cpp
	g++ -c src/oxuGameComponents/mapSelectButton.cpp

playField.o: src/oxuGameComponents/playField.cpp
	g++ -c src/oxuGameComponents/playField.cpp

graphicsHandler.o: src/oxuGameHandlers/graphicsHandler.cpp
	g++ -c src/oxuGameHandlers/graphicsHandler.cpp

hitObjectManager.o: src/oxuGameHandlers/hitObjectManager.cpp
	g++ -c src/oxuGameHandlers/hitObjectManager.cpp

inputHandler.o: src/oxuGameHandlers/inputHandler.cpp
	g++ -c src/oxuGameHandlers/inputHandler.cpp

mapManager.o: src/oxuGameHandlers/mapManager.cpp
	g++ -c src/oxuGameHandlers/mapManager.cpp

soundHandler.o: src/oxuGameHandlers/soundHandler.cpp
	g++ -c src/oxuGameHandlers/soundHandler.cpp

clean:
	rm *.o

#simple makefile
