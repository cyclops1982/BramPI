CXXFLAGS:=-std=c++17 -Wall -Wextra -g -pthread -lh2o-evloop -lssl -lcrypto -lwslay -Iext/simplesocket

PROGRAMS = brampi

all: $(PROGRAMS)

clean:
	rm -f *~ *.o *.d  $(PROGRAMS)

brampi: main.o h2o-pp.o ext/simplesocket/comboaddress.o
	g++ -o $@ $^ $(CXXFLAGS) 
