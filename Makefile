CXX=g++-9
CXX_STANDARD=--std=c++17
CXX_FLAGS=-O2 -Wall -DSPDLOG_COMPILED_LIB
CXX_INCLUDE_PATH=-Ivendor/spdlog/include -Isrc
LD_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lstdc++fs -lpthread

CXX_SRC = $(wildcard vendor/spdlog/src/*.cpp)         \
                                                      \
         $(wildcard src/oXu/beatmap/components/*.cpp) \
         $(wildcard src/oXu/beatmap/sections/*.cpp)   \
         $(wildcard src/oXu/utils/*.cpp)              \
         $(wildcard src/oXu/main.cpp)                 \
         $(wildcard src/oXu/core/*.cpp) 	          \
         $(wildcard src/oXu/components/*.cpp)         \
         $(wildcard src/oXu/beatmap/*.cpp )           \
         $(wildcard src/oXu/handlers/*.cpp)           \
         $(wildcard src/oXu/skin/*.cpp)               \
         $(wildcard src/oXu/core/threading/*.cpp)     \

OBJ = $(CXX_SRC:.cpp=.o)

CXX_GAME_SRC = $(filter-out $(wildcard vendor/spdlog/src/*.cpp), $(CXX_SRC))

GAME_OBJ = $(CXX_GAME_SRC:.cpp=.o)

release: $(OBJ)
	$(CXX) $^ -o oXu.out $(LD_FLAGS)
 
%.o: %.cpp
	$(CXX) $(CXX_STANDARD) $(CXX_FLAGS) $(CXX_INCLUDE_PATH) -c $< -o $@

.PHONY: clean clean-all

clean:
	rm $(GAME_OBJ)

clean-all:
	rm $(OBJ)
