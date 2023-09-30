#include "cmd.hpp"

void cmd::modeToClient(string arg, string line)
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
	string line;
	stringstream tmp;
	tmp = stringstream(arg);
	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	if (arg[0] == '#')
		modeToClient(arg, line);
		// modeToChannel(arg, line);
	// else
}