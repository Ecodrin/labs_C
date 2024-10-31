#ifndef LAB3_EX6_H
#define LAB3_EX6_H

#include <stdio.h>
#include <stdlib.h>

#include "../lib/SystemErrors/errors.h"

typedef struct Time {
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int sec;
} Time;

typedef struct Stop {
	Time start_stop;
	Time end_stop;
	char status_stop;  // Какая остановка
	struct Stop *next;
} Stop;

// Функции для обработки времени
int BiggerTime(Time *t1, Time *t2);
int IsCorrectTime(Time *time);
int DayInMonth(int month, int year);

#endif  // LAB3_EX6_H
