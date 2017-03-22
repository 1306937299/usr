#ifndef USER_LIST_H
#define USER_LIST_H

#include "userInfo.h"

typedef struct userList {
	userInfo_t data;	//数据域
	struct userList *next, *prev;
}sUserList, *pUserList;


pUserList userlist_init();

void userlist_destroy(pUserList p);

#endif
