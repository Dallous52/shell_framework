#include "main.h"
#include "log.h"

#ifdef __linux

#include <unistd.h>
#include <sys/wait.h>

void CreateWorkProc(const string& command, const vector<string>& option)
{
	pid_t pid;
	pid = fork();
	int error = 0;

	size_t argSize = option.size() + 2;
	char** myargs = new char* [argSize];

	switch (pid)//创建子进程，子进程返回0创建成功，父进程返回子进程PID
	{
	case -1:
		Error_insert_File(F_LOG, LOG_SERIOUS, "CreateWorkProc:> Child process %d creation failed", getpid());
		//子进程创建失败记录日志
		break;

	case 0:
		//子进程创建完成
		cout << "----------------------------------------------------------------------------------" << endl;
		
		//指令内容填写
		myargs[0] = (char*)command.c_str(); 
		if (!option.empty())
		{
			for (size_t i = 1; i < argSize; ++i)
			{
				myargs[i] = (char*)option[i - 1].c_str();
			}
		}
		myargs[argSize - 1] = NULL;
		
		error = execvp(myargs[0], myargs);
		if (error == -1)
		{
			cout << endl;
			cout << "[***" << "Command execution failed:> " << strerror(errno) << "***]" << endl;
			cout << endl;
			exit(0);
		}
		break;

	default:
		//父进程返回执行后续

		int wc = wait(NULL);
		cout << "----------------------------------------------------------------------------------" << endl;
		cout << "Command execution completed:> ";
		cout << "cpid = " << "[" << wc << "]" << endl << endl;
		break;
	}

	delete[]myargs;

	return;
}

#endif


#ifdef _WIN32

#include <Windows.h>
#include <tchar.h>
#include <comutil.h>  
#pragma comment(lib, "comsuppw.lib")

void CreateWorkProc(const string& command, const vector<string>& option)
{
#ifdef __MINGW32__ 
	char* szPath = new char[MAX_PATH];
#else
	wchar_t* szPath = new wchar_t[MAX_PATH];
#endif

	long ret = GetSystemDirectory(szPath, sizeof(wchar_t) * MAX_PATH);
	if (ret > MAX_PATH)
	{
		delete[]szPath;

#ifdef __MINGW32__ 
		szPath = new char[ret];
		ret = GetSystemDirectory(szPath, sizeof(char) * ret);
#else
		szPath = new wchar_t[ret];
		ret = GetSystemDirectory(szPath, sizeof(wchar_t) * ret);
#endif
	}

#ifdef __MINGW32__ 
	string str = szPath;
	str.append("\\cmd.exe");
#else
	wstring str = szPath;
	str.append(L"\\cmd.exe");
#endif

	STARTUPINFO si;
	memset(&si, 0, sizeof(si));

	si.cb = sizeof(si);
	si.wShowWindow = SW_SHOW;
	si.dwFlags = STARTF_USESHOWWINDOW;

	PROCESS_INFORMATION pi;
	memset(&pi, 0, sizeof(pi));

	string comm = "/c ";
	comm += command;
	for (int i = 0; i < option.size(); ++i)
	{
		comm += " " + option[i];
	}

	cout << "----------------------------------------------------------------------------------" << endl;

#ifdef __MINGW32__ 
	BOOL bRet = CreateProcess(str.c_str(), (char*)(comm).c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
#else
	BOOL bRet = CreateProcess(str.c_str(), (wchar_t*)s2ws(comm).c_str(), NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
#endif
	if (bRet)
	{
		WaitForSingleObject(pi.hProcess, INFINITE);// 等待程序退出

		cout << "----------------------------------------------------------------------------------" << endl;
		cout << "Command execution completed:> ";
		cout << "cpid = " << "[" << pi.dwProcessId << "]" << endl << endl;
		
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	else
	{
		Error_insert_File(F_LOG, LOG_SERIOUS, "CreateWorkProc:> Child process %ld creation failed", GetCurrentProcessId());
		//子进程创建失败记录日志
	}
}

#ifndef __MINGW32__ 

string ws2s(const wstring& ws)
{
	_bstr_t t = ws.c_str();
	char* pchar = (char*)t;
	string result = pchar;
	return result;
}


wstring s2ws(const string& s)
{
	_bstr_t t = s.c_str();
	wchar_t* pwchar = (wchar_t*)t;
	wstring result = pwchar;
	return result;
}

#endif

#endif // _WIN32

