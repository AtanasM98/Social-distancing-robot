PRODUCT=RobotCli

CPPFLAGS=-Iproduct -Itest

CXXFLAGS=-Wall -Werror -Wextra -pedantic -ggdb -std=c++11 -O0 $(CPPFLAGS)

SOURCES=$(wildcard robot/*.cpp) \
		$(wildcard robot/src/*.cpp) \
		$(wildcard robot/src/logic/*.cpp) \
		$(wildcard robot/src/dto/*.cpp) \
        $(wildcard include/*.cpp)

HEADERS=$(wildcard robot/*.h) \
        $(wildcard include/*.h) \
		$(wildcard include/*.hpp)

LDFLAGS= -lpthread

CXX=g++

.PHONY: all clean test

all: $(PRODUCT)
$(PRODUCT): $(SOURCES) $(HEADERS)
	@$(CXX) $(CXXFLAGS) $(SOURCES) -o $@ $(LDFLAGS)

clean:
	@rm -rf $(PRODUCT)

test: $(PRODUCT)
	@./$(PRODUCT)