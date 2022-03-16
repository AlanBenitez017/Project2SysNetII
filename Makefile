CXX = g++
CXXFLAGS = -g -std=c++11 -Wall -pthread -Wall -Werror=return-type -Werror=uninitialized

SRCS = $(wildcard *.hpp)
OBJECTS = $(SRCS: .hpp=.o)

all: clean server client

server: $(OBJECTS) Server/main.cpp Server/User.hpp Server/User.cpp Server/Server.cpp Server/Server.hpp ##location.hpp location.cpp common.hpp
		$(CXX) $(CXXFLAGS) -o $@ $^ -pthread

client: $(OBJECTS) Client/main.cpp Client/Client.hpp Client/Client.cpp
		$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf *.dSYM
		$(RM) *.o *.gc* test/*.o core server
