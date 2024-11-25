

/*
 * Файл с описанием заявок
 */

#ifndef LAB4_APPLICATION_H
#define LAB4_APPLICATION_H

#include <stdio.h>
#include <stdlib.h>

#include "../../lib2/SystemErrors2/errors.h"
#include "../../lib2/vector/charvector.h"

typedef struct Time {
	size_t year;
	size_t month;
	size_t day;
	size_t hour;
	size_t min;
	size_t sec;
} Time;

typedef struct Application {
	Time time_create;
	size_t priority;
	size_t id_department;
	String text;
} Application;

error_msg create_application(Application** application, Time time, size_t priority, size_t id_department, String* text);

error_msg copy_application_new(Application* src, Application** dst);

void destroy_application(Application* application);

#endif  // LAB4_APPLICATION_H
