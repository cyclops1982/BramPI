
#include "getcamerasettings.hh"
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-camera.h>
using namespace std;

static int getSettings() {
	Camera *camera;
	CameraWidget *widget;
	
	GPContext *context = gp_context_new();
	gp_camera_new(&camera);


	int retval = gp_camera_init(camera, context);
	if (retval != GP_OK) {
		cout<<"Failed to initialize camera: "<<retval<<endl;
		return retval;
	}

	retval = gp_camera_get_config(camera, &widget, context);
	if (retval != GP_OK) {
		cout <<"Failed to retrieve config settings:"<<retval<<endl;
		return retval;
	}


	gp_camera_exit(camera, context);
	return retval;
}

int main(int argc, char **argv) {
	int retval = getSettings();
	if (retval != GP_OK) {
		cout<<"Failed to get things:"<<retval<<endl;
	}

}
