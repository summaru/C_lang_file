#ifndef _TYPEDEF_H_
#define _TYPEDEF_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#define clean_out Sleep(1500);system("cls")
#define monmul(x) (1000*x)
typedef enum _type { TIME = 0, TUMOR = 1,NO_TYPE=2 }TYPE;
typedef enum _use { false_u = 0, true_u = 1 }USE;

static int 라면 = 1500;
static int 과자 = 1000;
typedef struct _payinfo {
	TYPE type;
	int time_tumor;
}payinfo;

typedef struct _person {
	char id[30];
	payinfo pay_info;
}person;

typedef struct _pcdata {
	int number_pc;
	USE y_n;
	person user;
}pcdata;

typedef struct _user_link {
	person user;
	struct _user_link *linkdata;
}user_link;
void clearReadBuffer();
#endif