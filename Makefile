CXXFLAGS:=-std=c++11 -Wall -Wextra -g -pthread

PROGRAMS = brampi

all: $(PROGRAMS)

clean:
	rm -f *~ *.o *.d  $(PROGRAMS)

brampi: main.cc
	g++ $(CXXFLAGS) -o $@ $^
