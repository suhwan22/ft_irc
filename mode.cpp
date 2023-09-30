#include "cmd.hpp"

void cmd::modeToChannel(string arg, string line)
{
	string line_two;
	stringstream tmp;
	tmp = stringstream(line);
	tmp >> line;
	getline(tmp, line_two, static_cast<char>(EOF));
	cout << "MODE CLIENT = " << arg << "MODE option = " << line << "MODE MSG = " << line_two << endl;
}

void cmd::mode(string arg)
{
	string msg;
	string line;
	stringstream tmp;
	tmp = stringstream(arg);
	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	if (arg[0] == '#')
		modeToChannel(arg, line);
	else {
		msg = "Error: parameters error\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
	}
}