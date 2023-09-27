#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"


cmd::cmd(int clntSock, char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist) : _clntSock(clntSock), _clilist(clilist), _chlist(chlist)
{
	string			receivedstring(buf, strlen);
	stringstream	ss(receivedstring);
	stringstream	tmp;
	string			line;
	content			content;

	while (getline(ss, line, '\n'))
	{
		tmp = stringstream(line);
		tmp >> line;
		content.cmd = line;
		getline(tmp, line, static_cast<char>(EOF));
		line.erase(0, 1);
		content.arg = line;
		_content.push_back(content);
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
	for (vector<content>::iterator it = _content.begin(); it != _content.end(); it++)
	{
		//tokens = splitCmd(*it);
		if ((*it).cmd == "PRIVMSG")
			privmsg((*it).arg);
		else if ((*it).cmd == "MODE")
			;
		else if ((*it).cmd == "PRIVMSG")
			;
		else if ((*it).cmd == "USER")
			;
		else if ((*it).cmd == "PASS")
			;
		else if ((*it).cmd == "NICK")
			;
		else
			;
	}
	// printCmdVector(*tokens);
	return 0;
}

void	cmd::printContent(const vector<content>& contents)
{
	for (vector<content>::const_iterator it = contents.begin(); it != contents.end(); it++)
		cout << "CMD : " << (*it).cmd << ", ARG : " << (*it).arg << endl;
}

const vector<content>& cmd::getContent() const
{
	return (_content);
}
