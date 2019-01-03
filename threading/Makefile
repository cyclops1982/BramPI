CXXFLAGS:=-std=c++11 -Wall -g -pthread
CFLAGS:= -Wall -O2 -MMD -MP -ggdb 

PROGRAMS = main

all: $(PROGRAMS)

clean:
	rm -f *~ *.o *.d  $(PROGRAMS)

-include *.d


main: main.o
	g++ -std=c++11 -Wall -g -pthread -o $@ $^
