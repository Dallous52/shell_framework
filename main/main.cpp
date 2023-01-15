#include "main.h"

int main(int argc, char* const* argv)
{
	while (true)
	{	
		string command;
		vector<string>	option;
		DisplayPrompt();
		ReadUserIn(command, option);

		if (command.empty())
			continue;

		if (command != "exit")
		{
			//cout << "Debug:> option.size = " << option.size() << endl;
			AppNameJudge(command);
			//cout << command << endl;
			CreateWorkProc(command, option);
		}
		else
		{
			break;
		}
	}
	return 0;
}