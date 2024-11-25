#include "application.h"



error_msg create_application(Application** app, Time time, size_t priority, size_t id_department, String* text){
	Application * application = (Application*)calloc(1, sizeof(Application));
	application->time_create = time;
	application->priority = priority;
	application->id_department = id_department;
	error_msg errorMsg = mstrcopynew(text, &(application->text));
	if(errorMsg.type){
		return errorMsg;
	}
	*app = application;
	return (error_msg){SUCCESS, "", ""};
}



void destroy_application(Application * application){
	destroy_string(&(application->text));
	free(application);
}

error_msg copy_application_new(Application * src, Application ** dst){
	error_msg errorMsg = create_application(dst, src->time_create, src->priority, src->id_department, &(src->text));
	if(errorMsg.type){
		return errorMsg;
	}
	return (error_msg){SUCCESS, "", ""};
}