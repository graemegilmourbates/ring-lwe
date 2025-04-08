CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)

main: $(OBJ) main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(OBJ)

clean:
	rm -f src/*.o main
