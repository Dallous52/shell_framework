#ifndef LOG
#define LOG

#include "Global.h"

#define LOG_FATAL		0 //致命
#define LOG_URGENT		1 //紧急
#define LOG_SERIOUS		2 //严重
#define LOG_CRIT		3 //批评
#define LOG_ERR			4 //错误
#define LOG_WARN		5 //警告 
#define LOG_NOTICE		6 //注意
#define LOG_INFO		7 //信息
#define LOG_DEBUG		8 //调试

#define ERR_NUM			9

#define OUT_LEVEL		4

#ifdef __linux
#define F_LOG			"sysinfo/log.txt"
#endif // linux

#ifdef _WIN32
#define F_LOG			"sysinfo\\log.txt"
#endif // _WIN32


//错误号相关名称
const string ErrorInfo[ERR_NUM] = {
	"fatal",
	"urgent",
	"serious",
	"critical",
	"error",
	"warn",
	"notice",
	"infomation",
	"debuge"
};


//向日志中输入程序错误		文件名			错误等级            错误内容
void Error_insert_File(const char* filename, int errLev, const char* error, ...);


//获取当前时间
string GetTime();

#endif // !LOG

