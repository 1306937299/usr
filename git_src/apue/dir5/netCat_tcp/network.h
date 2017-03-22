#ifndef NETWORK_H
#define NETWORK_H	//防止头文件重复包含
//头文件中应当包含：预处理命令（宏定义） 类型的定义 函数的声明  全局变量的声明

#include "../../apue.h"
#define SERVER_PORT	8888

typedef char c2s_t[64];	//client to server  type

enum s2c_type_t {
	S2C_NOEXIST, S2C_FILECONTENT, S2C_FILEEND
};

typedef struct {
	enum s2c_type_t type;	//报文类型
	char filecontent[64];	//文件内容
	int  size;				//文件内容的长度
}s2c_t;

#endif
