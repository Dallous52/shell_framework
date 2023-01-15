#ifndef MAIN
#define MAIN

#include "Global.h"

#ifdef __linux
#define F_APP "app/"
#endif // __linux

#ifdef _WIN32
#define F_APP "app\\"
#endif // _WIN32

const string EXE = ".exe";

//显示用户提示符
void DisplayPrompt();

//读取用户输入
void ReadUserIn(string& command, vector<string>& option);

//创建工作子进程
void CreateWorkProc(const string& command, const vector<string>& option);

//判断执行文件名是否为系统命令
void AppNameJudge(string& name);

#ifdef _WIN32

//wstring 转 string
string ws2s(const wstring& ws);

//string 转 wstring
wstring s2ws(const string& s);

#endif // _WIN32


#endif // !MAIN
