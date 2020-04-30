CC=g++
CPPFLAGS=-O2
LDFLAGS=-lSDL2 -lSDL2_image -lstdc++fs

CPPSRC = $(wildcard src/main.cpp) 		\
		 $(wildcard src/oxuUtils/*.cpp) \
		 $(wildcard src/oxuCore/*.cpp) 	\
		 $(wildcard src/oxuGameComponents/*.cpp) \
		 $(wildcard src/oxuGameHandlers/graphicsHandler.cpp) \
		 $(wildcard src/oxuGameHandlers/inputHandler.cpp) \
		 $(wildcard src/oxuGameHandlers/mapManager.cpp) \

OBJ = $(CPPSRC:.cpp=.o)

release: $(OBJ)
	$(CC) $^ -o oXu $(LDFLAGS)
 
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm $(OBJ)
