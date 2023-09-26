#include "cmd.hpp"

cmd::cmd(int clntSock, char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist) : _clntSock(clntSock), _clilist(clilist), _chlist(chlist)
{
	string receivedstring(buf, strlen);
	istringstream ss(receivedstring);
	string tmp;
	while (getline(ss, tmp, '\n'))
	{
		tmp >> _command;
		_arg.push_back(tmp);
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

Client	*cmd::serachClient(int sock)
{
	for (vector<Client *>::iterator it = _clilist.begin(); i != _clilist.end(); i++)
	{
		if ((*it)->_clntSock == sock)
			return (*it);
	}
	return (NULL);
}

int cmd::parsecommand() {
	vector<string> *tokens;
	
	for (vector<string>::iterator it = _arg.begin(); it != _arg.end(); ++it)
	{
		//tokens = splitCmd(*it);
		if (_command == "JOIN")
			;
		else if (_command == "MODE")
			;
		else if (_command == "PRIVMSG")
			;
		else if (_command == "USER")
			;
		else if (_command == "PASS")
			;
		else if (_command == "NICK")
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
