#ifndef LAB3_MAIL_H
#define LAB3_MAIL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "../lib/vector/charvector.h"
#include "../lib/mstring/mstring.h"



typedef struct Address{
	String city;
	String street;
	int house;
	String building;
	int apartment;
	String index;

}Address;

typedef struct Mail{
	Address address;
	double parcel_weight;
	String mail_id;
	String mail_create_time;
	String mail_receipt_time;
}Mail;

typedef struct Post{
	Address * address;
	Mail * mails;
} Post;


typedef struct Time{
	int day;
	int month;
	int year;
	int hour;
	int minute;
	int sec;
} Time;

// Функции по адресам
error_msg create_address_ptr(Address ** address, char * city, char * street, int house, char * building, int apartment, char * index);
error_msg create_address(Address * address, char * city, char * street, int house, char * building, int apartment, char * index);
void destroy_address_ptr(Address * address);
void destroy_address(Address *address) ;
void print_address(FILE *stream, Address *address);

// Функции по Почте
error_msg create_post(Post * post, int capacity_mails, char * city, char * street, int house, char * building, int apartment, char * index);
void print_post(FILE * stream, Post * post, int count_mails);
void destroy_post(Post *post, int count_mails);


error_msg create_mail(Mail *,char * city, char * street, int house, char * building, int apartment, char * index, double parcel_weight, char * mail_id, Time mail_create_time, Time mail_receipt_time);
void destroy_mail(Mail * mail);
void print_mail(FILE * stream, Mail * mail);

// Добавление письма
error_msg push_mail_into_post(Post * post, int* count_mails, int *size_post, Mail* mail);
error_msg find_mail_in_post(Post * post, Mail* mail, String* mail_id, int count_mails, int * index);
error_msg delete_mail_in_post(Post * post, String * mail_id, int* count_mails);

// Функции ищущие доставленные и не доставленные письма
error_msg find_received_mails(Post * post, int count_mail);
error_msg find_not_received_mails(Post *post, int count_mail);


error_msg scan_email(Mail * mail);
void clear_buffer();
#endif  // LAB3_MAIL_H



