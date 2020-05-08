CC=g++
CPPFLAGS=-O2
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lstdc++fs -lpthread

CPPSRC = $(wildcard src/main.cpp) 		\
		 $(wildcard src/utils/*.cpp) \
		 $(wildcard src/core/*.cpp) 	\
		 $(wildcard src/components/*.cpp) \
		 $(wildcard src/components/game/*.cpp) \
		 $(wildcard src/beatmap/*.cpp ) \
		 $(wildcard src/handlers/*.cpp) \

OBJ = $(CPPSRC:.cpp=.o)

release: $(OBJ)
	$(CC) $^ -o oXu $(LDFLAGS)
 
%.o: %.cpp
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm $(OBJ)
