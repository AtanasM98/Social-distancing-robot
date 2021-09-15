CXX=g++

CXXFLAGS = -Wall -Werror -Wextra -ggdb -std=c++11 -I -v

SRC = src/Map.cpp src/PathPlanner.cpp src/Vehicle.cpp src/TestMethods.cpp

.PHONY: all clean

all: clean main test

main: main.cpp
	@$(CXX) $(CXXFLAGS) -o $@ main.cpp $(SRC)

clean:
	@rm -f main test *.o *.a *.gch *.so *.exe

test: clean test-src/main.cpp
	@$(CXX) $(CXXFLAGS) -o $@ test-src/main.cpp $(SRC)