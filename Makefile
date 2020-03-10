CXX := g++
CXXFLAGS := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lpthread -lboost_system -lboost_filesystem -lbass -o oXu!
SRC_DIR := $(shell find src/ -type f -regex ".*\.cpp")
OBJS := $(patsubst %.cpp,%.o,$(SRC_DIR))

release:
	$(CXX) $(SRC_DIR) $(CXXFLAGS)

%.o: %.cpp
	$(CXX) -c $<

clean:
	rm *.o

