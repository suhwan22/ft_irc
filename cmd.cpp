#include "cmd.hpp"

cmd::cmd(char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist) : _clilist(clilist), _chlist(chlist)
{
	string receivedstring(buf, strlen);
	istringstream ss(receivedstring);
	string tmp;
	while (getline(ss, tmp, '\n'))
	{
		_command.push_back(tmp);
	}
}

cmd::~cmd() {}

vector<string> *cmd::splitCmd(string &str) {
	vector<string> *tokens = new vector<string>;
	istringstream	iss(str);
	string token;
	while (iss >> token) {
		(*tokens).push_back(token);
	}
	return tokens;
}

int cmd::parsecommand() {
	vector<string> *tokens;
	
	for (vector<string>::iterator it = _command.begin(); it != _command.end(); ++it)
	{
		tokens = splitCmd(*it);
		cout << tokens[1][0] << endl;
		if ((*tokens)[0] == "JOIN")
			;
		else if ((*tokens)[0] == "MODE")
			;
		else ;
	}
	// printCmdVector(*tokens);
	return 0;
}

void cmd::printCmdVector(const vector<string>& cmdVector) {
        for (vector<string>::const_iterator it = cmdVector.begin(); it != cmdVector.end(); ++it) {
        	cout << *it << endl;
	}
}

const vector<string>& cmd::getCommand() const
{
	return (_command);
}
