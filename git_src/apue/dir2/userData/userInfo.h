#ifndef USER_INFO_H
#define USER_INFO_H

#include "../../apue.h"
#include <stdint.h>
#define NAME_LEN	32
#define PASSWD_LEN	NAME_LEN

//枚举 是一个 无符号的整型数  unsigned int
enum {
	SEX_MALE, 
	SEX_FEMALE 
};

typedef struct {
	char 	login_name[NAME_LEN];
	char 	login_passwd[PASSWD_LEN];
	char 	user_name[NAME_LEN];
	uint8_t user_sex;
	uint8_t user_age;
}userInfo_t;

/*
userInfo_t a;
a.user_sex = SEX_MALE;
if ( a.user_sex == SEX_MALE )
*/
/*
 int8_t int16_t int32_t int64_t
 uint8_t uint16_t uint32_t uint64_t
 */

#endif
