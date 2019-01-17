#include <iostream>
#include <signal.h>
#include "h2o-pp.hh"


int main(int argc, char **argv) {
    signal(SIGPIPE, SIG_IGN); // Thx ahu.

    //TODO: Spin up a web service
    // Web service should host a simple app
    // App should allow you to:
    // 1. Take a photo
    // 2. Start a timelapse
    // 3. Preview the photos

    H2OWebserver service("localhost", 80);
	
	service.addDirectory("/", "./html"); 

	h2o_accept_ctx_t* ctx = service.addContext();
	service.addListener(ComboAddress("0.0.0.0:80"), ctx);
	service.runLoop();


	return 0;
}