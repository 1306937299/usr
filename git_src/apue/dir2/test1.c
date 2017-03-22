#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>

// 指针数组：  代替大型的判断语句
int main(int argc, char **argv)
{
	struct stat statres;
	int ret;
	const char *pmode[] = {
		"---", "--x", "-w-", "-wx", "r--", "r-x", "rw-", "rwx"
//	    0        1     10     11     100    101    110    111		
	};
	//-dcblps
	char ptype[] = {"\0pc\0d\0b\0-\0l\0s"};
	struct passwd * ppas;
	struct group *pgr;

	printf("%s\n", argv[1]);

	ret = stat(argv[1], &statres);//获得文件的属性 
	if ( ret != 0 ) {
		perror("stat()");	//打印错误原因
		return -1;
	}
	
	ppas = getpwuid(statres.st_uid);
	pgr = getgrgid(statres.st_gid);
	//rw-r--r-- 0100644  		
	printf("%c%s%s%s %d %s %s %d %d %s\n", ptype[(statres.st_mode&S_IFMT)>>12],
			pmode[(statres.st_mode>>6)&7], 
			pmode[(statres.st_mode>>3)&7],
			pmode[statres.st_mode&7], statres.st_nlink, 
			ppas->pw_name, pgr->gr_name, statres.st_size, 
			statres.st_mtime, argv[1]);

/*
	if ( S_ISREG(statres.st_mode) ) {
		printf("普通文件！\n");
	}
	else if ( S_ISDIR(statres.st_mode) ) {
		printf("目录文件！\n");
	}
//	else if () {
//		..
//	}
*/

	//if ( statres.st_mode&0400 )
	//if ( (statres.st_mode>>8)&1 )
/*
	if ( statres.st_mode & (1<<8) )  {
		printf("r");
	}
	else {
		printf("-");
	}
	if ( statres.st_mode & (1<<7) )  {
		printf("w");
	}
	else {
		printf("-");
	}
	if ( statres.st_mode & (1<<6) )  {
		printf("x\n");
	}
	else {
		printf("-\n");
	}
*/

	return 0;
}
