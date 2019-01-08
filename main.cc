#include <iostream>
#include <signal.h>


int main(int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN); // Thx ahu.



	return 0;
}