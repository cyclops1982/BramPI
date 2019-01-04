#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-camera.h>


static GPContext* create_context() {
	GPContext *context;
	context = gp_context_new();
	
	//gp_context_set_error_func( /// register function for error handling/reporting
	return context;
	
}

int canon_enable_capture (Camera *camera, GPContext *context) {
	CameraWidget		*widget = NULL;
	CameraWidgetType	type;
	int			ret;

	ret = gp_camera_get_single_config (camera, "capturetarget", &widget, context);
	if (ret < GP_OK) {
		fprintf (stderr, "camera_get_config failed: %d\n", ret);
		return ret;
	}

	ret = gp_widget_get_type (widget, &type);
	if (ret < GP_OK) {
		fprintf (stderr, "widget get type failed: %d\n", ret);
		goto out;
	}

	char *stuff = "Memory card";

	ret = gp_widget_set_value (widget, stuff);
	if (ret < GP_OK) {
		fprintf (stderr, "toggling Canon capture to %s failed with %d\n", stuff, ret);
		goto out;
	}
	/* OK */
	ret = gp_camera_set_single_config (camera, "capturetarget", widget, context);
	if (ret < GP_OK) {
		fprintf (stderr, "camera_set_config failed: %d\n", ret);
		return ret;
	}
out:
	gp_widget_free (widget);
	return ret;
}



static int capture() {
	int retval;
	Camera *camera;
	GPContext *context = create_context();

	CameraFilePath cameraFilePath;
	CameraFile *file;
	char *data;
	unsigned long int size;

	
	gp_camera_new(&camera);
	retval = gp_camera_init(camera, context);
	if (retval != GP_OK) {
		printf("Failed to initialize camera: %d\n", retval);
		return retval;
	}

	canon_enable_capture(camera, context);

	retval = gp_camera_capture(camera, GP_CAPTURE_IMAGE, &cameraFilePath, context);
	if (retval != GP_OK) {
		printf("Capture failed: %d\n", retval);
		return retval;
	}
	printf("Return value: %d\n", retval);
	printf("Path name: %s/%s\n", cameraFilePath.folder, cameraFilePath.name);

	retval = gp_file_new(&file);
	if (retval != GP_OK) {
		printf("Failed to gp_file_new: %d\n",retval);
		return retval;		
	}

	retval = gp_camera_file_get(camera, cameraFilePath.folder, cameraFilePath.name, GP_FILE_TYPE_PREVIEW, file, context);
	if (retval != GP_OK) {
		printf("Failed to retrieve file: %d\n",retval);
		return retval;
	}

	retval = gp_file_get_data_and_size(file, (const char**)&data, &size);
	if (retval != GP_OK) {
		printf("Failed to get data/size of file: %d\n",retval);
		return retval;
	}
	printf("FIle size: %ld\n", size);

	FILE *fd = fopen("test.cr2", "wb");
	if (fd) {
		int writen = fwrite(data, size, 1, fd);
		printf("  fwrite size %ld, written %d\n", size, writen);
		fclose(fd);
	}

	gp_camera_exit(camera, context);
	return retval;
}

int main(int argc, char **argv) {
	return capture();
}
