CC=g++
CPPFLAGS=-O2 -DSPDLOG_COMPILED_LIB
CPP_INCLUDE_PATH=-Ivendor/spdlog/include
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lstdc++fs -lpthread

CPPSRC = $(wildcard vendor/spdlog/src/*.cpp)    \
         $(wildcard src/utils/*.cpp)            \
         $(wildcard src/main.cpp) 		        \
		 $(wildcard src/core/*.cpp) 	        \
		 $(wildcard src/components/*.cpp)       \
		 $(wildcard src/components/game/*.cpp)  \
		 $(wildcard src/beatmap/*.cpp )         \
		 $(wildcard src/handlers/*.cpp)         \

OBJ = $(CPPSRC:.cpp=.o)

release: $(OBJ)
	$(CC) $^ -o oXu $(LDFLAGS)
 
%.o: %.cpp
	$(CC) $(CPPFLAGS) $(CPP_INCLUDE_PATH) -c $< -o $@

clean:
	rm $(OBJ)
