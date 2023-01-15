#include "main.h"

#ifdef __linux
#include <dirent.h>
#endif // __linux

#ifdef _WIN32
#include <io.h>
#endif // _WIN32

static void GetFileName(string path, unordered_set<string>& files);

void DisplayPrompt()
{
	cout << "Manage System:> ";
}


void ReadUserIn(string& command, vector<string>& option)
{
	//获取用户输入
	string input;
	getline(cin, input);

	bool isCommand = true;
	string temp;

	//cout << "Debug:> input.size = " << input.size() << endl;

	//指令与参数分离
	for (size_t i = 0; i < input.size(); ++i)
	{
		if (input[i] == ' ')
		{
			if (!isCommand)
			{
				option.push_back(temp);
				temp.clear();
			}
			else
			{
				isCommand = false;
			}
			continue;
		}

		if (isCommand)
		{
			command.push_back(input[i]);
		}
		else
		{
			temp.push_back(input[i]);
		}
	}

	if (!temp.empty())
	{
		option.push_back(temp);
	}
}


void AppNameJudge(string& name)
{
	string tmp = name;
	unordered_set<string> files;
	GetFileName(F_APP, files);

#ifdef _WIN32
	tmp += EXE;
#endif // _WIN32

	if (files.find(tmp) == files.end())
	{
		return;
	}

	name = F_APP + tmp;
}


#ifdef __linux

static void GetFileName(string path, unordered_set<string>& files)
{
	DIR* pDir;   //  是头文件<dirent.h>的类型
	struct dirent* ptr;  // opendir、readdir这些都是头文件dirent.h

	//判断文件是否存在
	if (!(pDir = opendir(path.c_str())))
		return;

	while ((ptr = readdir(pDir)) != 0)
	{
		if (strcmp(ptr->d_name, ".") != 0 && strcmp(ptr->d_name, "..") != 0)
		{
			files.insert(ptr->d_name);  // 可以只保留名字
		}
	}

	closedir(pDir);
}

#endif // __linux


#ifdef _WIN32

static void GetFileName(string path, unordered_set<string>& files)
{
	// 用来存储文件信息的结构体，在头文件 <io.h>
	struct _finddata_t fileinfo;  // _finddata_t 这是一个struct类，c++中可以不要前面的struct的

	intptr_t hFile = 0;

	string p;  // 不在这p(path)初始化

	// 第一次查找
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			// 如果找到的是文件夹
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				continue;	// 不想进入文件夹，就在这里continue

				//if (std::strcmp(fileinfo.name, ".") != 0 && std::strcmp(fileinfo.name, "..") != 0)
				//{
				//	// 进入查找
				//	files.insert(p.assign(path).append("\\").append(fileinfo.name));
				//	GetAllFiles(p.assign(path).append("\\").append(fileinfo.name), files);
				//}
			}
			// 如果找到的不是文件夹
			else
			{
				// 保存的是文件名
				files.insert(p.assign(fileinfo.name));
				// 也可以是保存绝对路径
				// files.push_back(p.assign(path).append("\\").append(fileinfo.name));  
			}
		} while (_findnext(hFile, &fileinfo) == 0);

		// 结束查找
		_findclose(hFile);
	}
}

#endif // _WIN32

