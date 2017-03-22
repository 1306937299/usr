#include "userList.h"
//功能：对用户数据进行管理  
//链表       
//链表的头结点：数据域为空的结点，用它来管理整个链表

const char *pmenu = "1.Insert 2.Delete 3.Search 4.Print 5.Save 6.Quit:";

enum {
	INSERT=1, DELETE, SEARCH, PRINT, SAVE, QUIT
};

void insert_func(pUserList phead);
void delete_func(pUserList phead);
void search_func(pUserList phead);
void  print_func(pUserList phead);
void   save_func(pUserList phead);
void   load_func(pUserList phead);


void (*pfunc[])(pUserList) = {
	NULL, insert_func, delete_func, search_func, print_func, save_func
};

int main()
{
	pUserList phead; //头结点指针
	unsigned int choose;

	phead = userlist_init();
	load_func(phead);

	while (1) {
		printf(pmenu);
		scanf("%u", &choose);   // %d %u %ld %lld %lu %llu
		if (  choose < INSERT || choose > QUIT ) {
			continue;
		}
		if ( choose == QUIT ) 
			break;

		pfunc[choose](phead);

	}

	return 0;
}


void insert_func(pUserList phead)
{
	printf("[%s]\n", __func__);	//__LINE__ __FILE__
	pUserList pnew, ptrav;

	pnew = userlist_init();
	printf("input the login name:");
	scanf("%s", pnew->data.login_name);
	printf("input the login passwd:");
	scanf("%s", pnew->data.login_passwd);
	printf("input the user name:");
	scanf("%s", pnew->data.user_name);
	do {
		printf("input the user sex(1:男性 2:女性):");
		scanf("%u", &pnew->data.user_sex);
	} while ( pnew->data.user_sex != 1 && pnew->data.user_sex != 2 );
	do {
		printf("input the user age:");
		scanf("%u", &pnew->data.user_age);
	} while ( pnew->data.user_age <=0 || pnew->data.user_age >= 250 );
	

	for ( ptrav=phead->next; ptrav!=phead; ptrav=ptrav->next) {
		if ( strcmp(pnew->data.login_name, ptrav->data.login_name) == 0 ) {
			printf("Insert Failed.\n");
			userlist_destroy(pnew);
			return ;
		}
	}

	pnew->prev = phead->prev;
	pnew->next = phead;
	phead->prev->next = pnew;
	phead->prev = pnew;
}
void delete_func(pUserList phead)
{
	printf("[%s]\n", __func__);
	pUserList ptrav;
	char name_buf[NAME_LEN];
	printf("input delete name:");
	scanf("%s", name_buf);

	for ( ptrav=phead->next; ptrav!=phead; ptrav=ptrav->next) {
		if ( strcmp(name_buf, ptrav->data.login_name) == 0 ) {
			ptrav->next->prev = ptrav->prev;
			ptrav->prev->next = ptrav->next;
			userlist_destroy(ptrav);
			return ;
		}
	}
	printf("Not Find.\n");
}
void search_func(pUserList phead)
{//按登录名查找  
	printf("[%s]\n", __func__);
	pUserList ptrav;
	char name_buf[NAME_LEN];
	printf("input search name:");
	scanf("%s", name_buf);

	for ( ptrav=phead->next; ptrav!=phead; ptrav=ptrav->next) {
		if ( strcmp(name_buf, ptrav->data.login_name) == 0 ) {
			printf("[%s,%s,%s,%s,%d]\n", ptrav->data.login_name, 
				ptrav->data.login_passwd, 
				ptrav->data.user_name,
				psex[ptrav->data.user_sex], 
				ptrav->data.user_age);
			return ;
		}
	}
	printf("Not Find.\n");
}

void  print_func(pUserList phead)
{
	printf("[%s]\n", __func__);
	pUserList ptrav;

	printf("HEAD->");
	for ( ptrav=phead->next; ptrav!=phead; ptrav=ptrav->next) {
		printf("[%s,%s,%s,%s,%d]->", ptrav->data.login_name, 
				ptrav->data.login_passwd, 
				ptrav->data.user_name,
				psex[ptrav->data.user_sex], 
				ptrav->data.user_age);
	}
	printf("HEAD\n");

}

void   save_func(pUserList phead)
{
	printf("[%s]\n", __func__);
	int fd;

	fd = open(USERDATA_FILE, O_WRONLY|O_CREAT|O_TRUNC, 0644);
	if ( fd < 0 ) {
		perror("open()");
		return ;
	}

	pUserList ptrav;

	for ( ptrav=phead->next; ptrav!=phead; ptrav=ptrav->next) {
		write(fd, &ptrav->data, sizeof(userInfo_t));
	}

	close(fd);
}

void   load_func(pUserList phead)
{
	printf("[%s]\n", __func__);
	int fd;
	int ret;
	pUserList pnew;

	fd = open(USERDATA_FILE, O_RDONLY);
	if ( fd < 0 ) {
		perror("open()");
		return ;
	}

	while (1) {
		pnew = userlist_init();
		ret = read(fd, &pnew->data, sizeof(userInfo_t));
		if ( ret <= 0 ) {
			userlist_destroy(pnew);
			break;
		}
		pnew->prev = phead->prev;
		pnew->next = phead;
		phead->prev->next = pnew;
		phead->prev = pnew;
	}

	close(fd);
}
