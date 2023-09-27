#include "cmd.hpp"

cmd::cmd(int clntSock, char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist) : _clntSock(clntSock), _clilist(clilist), _chlist(chlist)
{
	string			receivedstring(buf, strlen);
	stringstream	ss(receivedstring);
	stringstream	tmp;
	string			line;

	while (getline(ss, line, '\n'))
	{
		tmp = stringstream(line);
		//getline(tmp, line, ' ');
		tmp >> line;
		_command.push_back(line);
		getline(tmp, line, static_cast<char>(EOF));
		_arg.push_back(line);
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

Client	*cmd::searchClient(int sock)
{
	for (vector<Client *>::iterator it = _clilist.begin(); it != _clilist.end(); it++)
	{
		if ((*it)->getSock() == sock)
			return (*it);
	}
	return (NULL);
}

int cmd::parsecommand() {
	vector<string> *tokens;
	
	for (vector<string>::iterator it = _arg.begin(); it != _arg.end(); ++it)
	{
		//tokens = splitCmd(*it);
		if ((*it) == "JOIN")
			;
		else if ((*it) == "MODE")
			;
		else if ((*it) == "PRIVMSG")
			;
		else if ((*it) == "USER")
			;
		else if ((*it) == "PASS")
			;
		else if ((*it) == "NICK")
			;
		else ;
	}
	// printCmdVector(*tokens);
	return 0;
}

void cmd::printCmdVector(const vector<string>& cmdVector, const vector<string>& argVector)
{
//	for (vector<string>::const_iterator it = cmdVector.begin(); it != cmdVector.end(); ++it) {
//        cout << "CMD : " << *it << ", ARG : " << << endl;
//			cout << *arg << " "
//	}
	int i;
	
	for (i = 0; i < cmdVector.size(); i++)
		cout << "CMD : " << cmdVector[i] << ", ARG : " << argVector[i] << endl;
}

const vector<string> cmd::getCommand() const
{
	return (_command);
}

const vector<string> cmd::getArgument() const
{
	return (_arg);
}
