#ifndef NETWORK_H
#define NETWORK_H

#include "userInfo.h"

/* 
 * 客户端-->服务器  
 */

// 类型 enum c2s_req_type 为 客户端->服务器的网络数据报文类型
enum c2s_req_type { 
	C2S_REQ_MINFLAG,		//枚举值最小值标志
	C2S_REQ_REGISTER,		//注册请求
	C2S_REQ_LOGIN,			//登录请求
	C2S_REQ_CHANGEPW,		//修改密码请求
	C2S_REQ_CAT,			//显示文件请求
	C2S_REQ_QUIT,			//退出请求
	C2S_REQ_MAXFLAG			//枚举值最大值标志
};
// 类型 c2s_req_register_arg_t 为 客户端->服务器的注册请求携带的相关参数
typedef userInfo_t c2s_req_register_arg_t;
// 类型 c2s_req_login_arg_t 为 客户端->服务器的登录请求携带的相关参数
typedef struct {
	char login_name[NAME_LEN];
	char login_passwd[PASSWD_LEN];
}c2s_req_login_arg_t;
// 类型 c2s_req_changepw_arg_t 为 客户端->服务器的修改密码请求携带的相关参数
typedef struct {
	char login_name[NAME_LEN];
	char old_passwd[PASSWD_LEN];
	char new_passwd[PASSWD_LEN];
}c2s_req_changepw_arg_t;
// 类型 c2s_req_cat_arg_t 为 客户端->服务器的显示文件请求携带的相关参数
typedef struct {
	char filename[NAME_LEN];
}c2s_req_cat_arg_t;
// 类型 c2s_req_t 为 客户端->服务器的网络数据报文
typedef struct {
	enum c2s_req_type req_type;	//报文类型
	union {
		c2s_req_register_arg_t 	register_arg;
		c2s_req_login_arg_t		login_arg;
		c2s_req_changepw_arg_t	changepw_arg;
		c2s_req_cat_arg_t		cat_arg;
	}req_arg;//不同报文类型对应的不同相关参数
}c2s_req_t;


/*
 * 服务器-->客户端
 */

//类型 enum s2c_rep_type 为 服务器->客户端的网络数据报文类型
enum s2c_rep_type {
	S2C_REP_MINFLAG,		//枚举值最小值标志
	S2C_REP_REGISTER,		//注册请求的应答
	S2C_REP_LOGIN,			//登录请求的应答
	S2C_REP_CHANGEPW,		//修改该密码请求的应答
	S2C_REP_CAT,			//显示文件内容请求的应答
	S2C_REP_MAXFLAG			//枚举值最大值标志
};

// 类型 s2c_rep_register_arg_t 为 服务器->客户端的注册请求应答携带的相关参数
typedef struct {
	enum {
		S2C_REP_REGISTER_ACCEPT,	//注册成功
		S2C_REP_REGISTER_REJECT		//注册失败
	}op;
}s2c_rep_register_arg_t;
// 类型 s2c_rep_login_arg_t 为 服务器->客户端的登录请求应答报文
typedef struct {
	enum {
		S2C_REP_LOGIN_ACCEPT,		//登录成功
		S2C_REP_LOGIN_REJECT		//登录失败
	}op;
	char login_name[NAME_LEN];
	char real_name[NAME_LEN];
	uint8_t user_sex;
	uint8_t user_age;
}s2c_rep_login_arg_t;
// 类型 s2c_rep_changepw_arg_t 为 服务器->客户端的修改密码请求应答报文
typedef struct {
	enum {
		S2C_REP_CHANGEPW_ACCEPT,	//修改成功
		S2C_REP_CHANGEPW_REJECT,	//修改失败
	}op;
}s2c_rep_changepw_arg_t;
// 类型 s2c_rep_cat_arg_t 为 服务器->客户端的显示文件内容请求应答报文
typedef struct {
	enum {
		S2C_REP_CAT_NOEXIST,		//不存在
		S2C_REP_CAT_EXIST,			//存在
	}op;
}s2c_rep_cat_arg_t;
// 类型 s2c_rep_t 为 服务器->客户端的网络数据报文
typedef struct {
	enum s2c_rep_type rep_type;
	union {
		s2c_rep_register_arg_t 	register_arg;
		s2c_rep_login_arg_t		login_arg;		
		s2c_rep_changepw_arg_t	changepw_arg;
		s2c_rep_cat_arg_t		cat_arg;
	}rep_arg;
}s2c_rep_t;


#endif 
