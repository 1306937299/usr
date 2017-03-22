#ifndef USER_INFO_H
#define USER_INFO_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define NAME_LEN	32
#define PASSWD_LEN	64

enum {
	SEX_MALE = 1, 
	SEX_FEMALE
};//unsigned int

typedef struct {
	char 	login_name[NAME_LEN];
	char 	login_passwd[PASSWD_LEN];
	char 	real_name[NAME_LEN];
	uint8_t user_sex;
	uint8_t user_age;
}userInfo_t;


#endif
