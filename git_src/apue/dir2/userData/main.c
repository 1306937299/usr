#include "userList.h"
//功能：对用户数据进行管理  
//链表       
//链表的头结点：数据域为空的结点，用它来管理整个链表

const char *pmenu = "1.Insert 2.Delete 3.Search 4.Print 5.Quit:";

enum {
	INSERT=1, DELETE, SEARCH, PRINT, QUIT
};

void insert_func(pUserList phead);
void delete_func(pUserList phead);
void search_func(pUserList phead);
void  print_func(pUserList phead);


void (*pfunc[])(pUserList) = {
	NULL, insert_func, delete_func, search_func, print_func
};

int main()
{
	pUserList phead; //头结点指针
	unsigned int choose;

	phead = userlist_init();
	while (1) {
		printf(pmenu);
		scanf("%u", &choose);   // %d %u %ld %lld %lu %llu
		if (  choose < INSERT || choose > QUIT ) {
			continue;
		}
		if ( choose == QUIT ) 
			break;

		pfunc[choose](phead);

		/*
		switch ( choose ) {
			case INSERT:
				{
					insert_func(phead);
					break;
				}
			case DELETE:
				{
					delete_func(phead);
					break;
				}
			case SEARCH:
				{
					search_func(phead);
					break;
				}
			case PRINT:
				{
					print_func(phead);
					break;
				}
		}
		*/
	}
	

	return 0;
}


void insert_func(pUserList phead)
{
	printf("[%s]\n", __func__);	//__LINE__ __FILE__
}
void delete_func(pUserList phead)
{
	printf("[%s]\n", __func__);
}
void search_func(pUserList phead)
{
	printf("[%s]\n", __func__);
}
void  print_func(pUserList phead)
{
	printf("[%s]\n", __func__);
}
