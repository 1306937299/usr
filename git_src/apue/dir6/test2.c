#include "../apue.h"
#include <glob.h>


//./exe /var/ftp/homework_2
int main(int argc, char **argv)
{
	struct stat statres;
	int ret;
	glob_t globres;
	int i;

	if ( argc != 2 ) {
		fprintf(stderr, "Usage ...\n");
		return -1;
	}

	//1.判断argv[1]这个路径是否存在
	ret = stat(argv[1], &statres);
	if ( ret != 0 ) {
		fprintf(stderr, "%s is not exist!\n", argv[1]);
		return -1;
	}
	
	//2.判断这个路径是否是一个目录
	if ( !S_ISDIR(statres.st_mode) ) {
		fprintf(stderr, "%s is not a directory!\n", argv[1]);
		return -1;
	}

	//3.显示目录中的所有文件
	char buf[128];
	sprintf(buf, "%s/*", argv[1]);	// "/var/ftp/homework_2/*"
	//strcpy(buf, argv[1]);
	//strcat(buf, "/*");
	//glob 在文件系统中搜索匹配的路径
	glob(buf , 0, NULL, &globres);

	for ( i=0; i<globres.gl_pathc; i++) {
		char *p;
		int j;

		for ( j=0, p=globres.gl_pathv[i]; globres.gl_pathv[i][j]!='\0'; j++) {
			if ( globres.gl_pathv[i][j] == '/' && globres.gl_pathv[i][j+1] != '\0' ) {
				p = &globres.gl_pathv[i][j+1];
			}
		}
		
		puts(p);
	} 

	globfree(&globres);
	return 0;
}
