
#include "getcamerasettings.hh"
#include <string.h>
#include <gphoto2/gphoto2.h>
#include <gphoto2/gphoto2-context.h>
#include <gphoto2/gphoto2-camera.h>
using namespace std;


inline const char* ToString(CameraWidgetType v)
{
	switch (v)
	{
		case GP_WIDGET_WINDOW:   return "Window";
			/* Window widget
				 *   This is the toplevel configuration widget. It should likely contain multiple #GP_WIDGET_SECTION entries.
				 */
		case GP_WIDGET_SECTION:   return "Section"; /* Section widget (think Tab) */
		case GP_WIDGET_TEXT: return "Text - Char";
		case GP_WIDGET_RANGE: return "Slider Widget - float";
		case GP_WIDGET_TOGGLE: return "Toggle - int"; /* Toggle widget (think check box) */
		case GP_WIDGET_RADIO: return "Radio button - char"; /* Radio button widget */
		case GP_WIDGET_MENU: return "Menu widget - char"; /* Same as RADIO */
		case GP_WIDGET_BUTTON: return "Button press - CameraWidgetCallback"; 
		case GP_WIDGET_DATE: return "Date - int";
		default: return "[Unknown WidgetType]";
	}
}


std::string OutputSpaces(int amount) {
	std::string blanks(amount, ' ');
	return blanks;
}

int PrintWidget(CameraWidget *widget, int depth=0) {
	depth++;
	CameraWidgetType widgetType;
	CameraWidget *childWidget;
	int retval;

	retval = gp_widget_get_type(widget, &widgetType);
	if (retval != GP_OK) {
		cout <<depth<<OutputSpaces(depth)<<"Failed to retrieve Type:"<<retval<<endl;
		return retval;
	}
	cout <<depth<<OutputSpaces(depth)<<"Type: "<<ToString(widgetType)<<endl;

	const char *label;
	retval = gp_widget_get_label(widget, &label);
	if (retval != GP_OK) {
		cout <<depth<<OutputSpaces(depth)<<"Failed to retrieve label:"<<retval<<endl;
		return retval;
	}
	cout <<depth<<OutputSpaces(depth)<<"Label: "<<label<<endl;

	const char *name;
	retval = gp_widget_get_name(widget, &name);
	if (retval != GP_OK) {
		cout <<depth<<OutputSpaces(depth)<<"Failed to retrieve name:"<<retval<<endl;
		return retval;
	}
	cout <<depth<<OutputSpaces(depth)<<"Name: "<<name<<endl;

	cout <<depth<<OutputSpaces(depth)<<"Value:";
	switch(widgetType) {
		case GP_WIDGET_WINDOW:
		case GP_WIDGET_SECTION:
			cout <<"(Window/Section - VALUE = NONE)"<<endl;		
			break;
		case GP_WIDGET_TEXT:
			
			char *value;
			retval = gp_widget_get_value(widget, &value);
			if (retval != GP_OK) {
				cout<<" FAILED !! "<<retval;
			} else {
				cout<<value;
			}
			cout<<endl;
		break;

		case GP_WIDGET_RANGE:
			float *f;
			retval = gp_widget_get_value(widget, &f);
			if (retval != GP_OK) {
				cout<<" FAILED !! "<<retval;
			} else {
				cout<<f;
			}
			cout<<endl;
		break;

		case GP_WIDGET_TOGGLE: 
			int *i;
			retval = gp_widget_get_value(widget, &i);
			if (retval != GP_OK) {
				cout<<" FAILED !! "<<retval;
			} else {
				cout<<i;
			}
			cout<<endl;
		break;

		case GP_WIDGET_RADIO:
		case GP_WIDGET_MENU:
			char *r;
			int choices;
			retval = gp_widget_get_value(widget, &r);
			if (retval != GP_OK) {
				cout<<" FAILED !! "<<retval;
			} else {
				cout<<r;
			}
			cout<<endl;
			
			choices = gp_widget_count_choices(widget);
			if (choices > 0) {
				cout <<depth<<OutputSpaces(depth)<<"Choices: "<<endl;
				for(int ch=0;ch<choices;++ch) {
					const char *choice;
					retval = gp_widget_get_choice(widget, ch, &choice);
					if (retval != GP_OK) {
						cout <<depth<<OutputSpaces(depth+2)<<"Failed to retrieve choice:"<<retval<<endl;	
					}
					cout <<depth<<OutputSpaces(depth+2)<<choice<<endl;
				}
			}
		break;

		case GP_WIDGET_BUTTON: 
			cout<<"Button/callback - no value?"<<endl;
		break;

		case GP_WIDGET_DATE:
			int *d;
			retval = gp_widget_get_value(widget, &d);
			if (retval != GP_OK) {
				cout<<" FAILED !! "<<retval;
			} else {
				cout<<"(date)"<<d;
			}
			cout<<endl;

		break;
		default: cout<<"UNKNOWN"<<endl;

	}


	int childCount = gp_widget_count_children(widget);
	if (childCount > 0) {
		cout <<depth<<OutputSpaces(depth)<<" Has "<<childCount<<" children"<<endl;

		for (int i=0;i<childCount;++i) {
			cout <<depth<<OutputSpaces(depth)<<" Retrieving child "<<i<<endl;

			retval = gp_widget_get_child(widget, i, &childWidget);
			if (retval != GP_OK) {
				cout <<depth<<OutputSpaces(depth)<<"Failed to get child nr "<<childCount<<".Error:"<<retval<<endl;		
				return retval;
			}
			retval = PrintWidget(childWidget, depth);
			if (retval != GP_OK) {
				cout <<depth<<OutputSpaces(depth)<<"Failed to run printwidget. Error:"<<retval<<endl;		
			}
		}
	}
	cout<<endl;
	return GP_OK;
}


static int getSettings() {
	Camera *camera;
	CameraWidget *widget;
	int retval = GP_OK;
	
	GPContext *context = gp_context_new();
	gp_camera_new(&camera);


	retval = gp_camera_init(camera, context);
	if (retval != GP_OK) {
		cout<<"Failed to initialize camera: "<<retval<<endl;
		return retval;
	}

	retval = gp_camera_get_config(camera, &widget, context);
	if (retval != GP_OK) {
		cout <<"Failed to retrieve config settings:"<<retval<<endl;
		return retval;
	}

	retval = PrintWidget(widget);
	if (retval != GP_OK) {
		cout <<"Failed to print widget correctly:"<<retval<<endl;
		return retval;
	}

	cout<<"Done!"<<endl;
	gp_widget_free(widget);
	gp_camera_exit(camera, context);
	return retval;
}

int main(int argc, char **argv) {
	int retval = getSettings();
	if (retval != GP_OK) {
		cout<<"Failed to get things:"<<retval<<endl;
	}

}
