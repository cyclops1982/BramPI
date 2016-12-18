#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "gphoto2/gphoto2.h"
#include "gphoto2/gphoto2-context.h"
#include "gphoto2/gphoto2-camera.h"


static GPContext* create_context() {
	GPContext *context;
	context = gp_context_new();
	
	//gp_context_set_error_func( /// register function for error handling/reporting
	return context;
	
}


static int capture() {
	int retval;
	Camera *camera;
	GPContext *context = create_context();

	CameraFilePath cameraFilePath;
	
	gp_camera_new(&camera);
	retval = gp_camera_init(camera, context);
	if (retval != GP_OK) {
		printf("Failed to initialize camera: %d\n", retval);
		return retval;
	}

	retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &cameraFilePath, context);
	if (retval != GP_OK) {
		printf("Capture failed: %d\n", retval);
		return retval;
	}
	printf("Return value: %d\n", retval);
	printf("Path name: %s/%s\n", cameraFilePath.folder, cameraFilePath.name);
	

	gp_camera_exit(camera, context);
	return retval;
}

int main(int argc, char **argv) {
	return capture();
}
