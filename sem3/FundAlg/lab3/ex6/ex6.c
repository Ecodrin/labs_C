#include "ex6.h"



int DayInMonth(int month, int year) {
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0))) {
		return 29;
	}
	return days[month - 1];
}

int IsCorrectTime(Time *time) {
	if (time->year < 0 || time->year > 9999 || time->month < 1 || time->month > 12 || time->day < 0 ||
	    time->day > DayInMonth(time->month, time->year))
		return 0;
	if (time->hour < 0 || time->hour >= 24 || time->minute < 0 || time->minute >= 60 || time->sec < 0 ||
	    time->sec >= 60)
		return 0;

	return 1;
}

int BiggerTime(Time *t1, Time *t2) {
	if (t1->year > t2->year || (t1->year == t2->year && t1->month > t2->month) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day > t2->day) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day == t2->day && t1->hour > t2->hour) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day == t2->day && t1->hour == t2->hour &&
	     t1->minute > t2->minute) ||
	    (t1->year == t2->year && t1->month == t2->month && t1->day == t2->day && t1->hour == t2->hour &&
	     t1->minute == t2->minute && t1->sec > t2->sec))
		return 0;
	return 1;
}