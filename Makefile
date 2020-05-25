CXX=g++
CXXFLAGS=-O2 -Wall -DSPDLOG_COMPILED_LIB
CXX_INCLUDE_PATH=-Ivendor/spdlog/include -Isrc
LDFLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lstdc++fs -lpthread

CXXSRC = $(wildcard vendor/spdlog/src/*.cpp)    \
                                                \
         $(wildcard src/oXu/utils/*.cpp)            \
         $(wildcard src/oXu/main.cpp)               \
         $(wildcard src/oXu/core/*.cpp) 	        \
         $(wildcard src/oXu/components/*.cpp)       \
         $(wildcard src/oXu/components/game/*.cpp)  \
         $(wildcard src/oXu/beatmap/*.cpp )         \
         $(wildcard src/oXu/handlers/*.cpp)         \
         $(wildcard src/oXu/skin/skinManager.cpp)  \

OBJ = $(CXXSRC:.cpp=.o)

CXX_GAME_SRC = $(filter-out $(wildcard vendor/spdlog/src/*.cpp), $(CXXSRC))

GAME_OBJ = $(CXX_GAME_SRC:.cpp=.o)

release: $(OBJ)
	$(CXX) $^ -o oXu $(LDFLAGS)
 
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(CXX_INCLUDE_PATH) -c $< -o $@

.PHONY: clean clean-all

clean:
	rm $(GAME_OBJ)

clean-all:
	rm $(OBJ)
