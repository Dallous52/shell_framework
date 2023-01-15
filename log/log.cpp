#include "log.h"

#ifdef _WIN32
#include <direct.h>
#include <time.h>
#endif

void Error_insert_File(const char* filename, int errLev, const char* error, ...)
{
	//获取可变参数
	va_list vapa;
	va_start(vapa, error);
	
	char buf[500];
	vsprintf(buf, error, vapa);

Reopen:
	ofstream log(filename, ios::out | ios::app);
	if (!log.is_open())//日志打开失败处理
	{
		if (errno == ENOENT)
		{
			int ret;
#ifdef _WIN32
			ret = _mkdir("sysinfo");
#endif

#ifdef __linux
			ret = mkdir("sysinfo", 0755);
#endif // __linux

			if (ret == -1)
			{
				cerr << "Make directory [sysinfo] failed." << endl;
				exit(0);
			}

			goto Reopen;
		}
		else
		{
			cerr << "log file open failed : " << strerror(errno) << endl;
			return;
		}
	}

	string currTime = GetTime();

	//错误信息输入日志文件
	if (errLev >= 0 && errLev < ERR_NUM)
	{
		if (errLev < OUT_LEVEL)//判断是否输出与屏幕
		{
			cerr << currTime << " [" << ErrorInfo[errLev] << "] " << buf << endl;
		}

		string err = currTime + " [" + ErrorInfo[errLev] + "] " + buf + "\n";
		//********记得加时间
		log << err;
	}

	log.close();
}


string GetTime()
{
	string date;
	time_t times;
	struct tm* timed;
	char ansTime[50];

	time(&times); //获取从1900至今过了多少秒，存入time_t类型的timep
	timed = localtime(&times);//用localtime将秒数转化为struct tm结构体

	sprintf(ansTime, "%d-%02d-%02d %02d:%02d:%02d", 1900 + timed->tm_year, 1 + timed->tm_mon,
		timed->tm_mday, timed->tm_hour, timed->tm_min, timed->tm_sec);

	date = ansTime;

	return date;
}