#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

cmd::cmd(int clntSock, char *buf, int strlen, string servpass, vector<Client *> &clntList, vector<Channel *> &chList) : _clntSock(clntSock), _clntList(clntList), _chList(chList), _servPass(servpass)
{
	string			input(buf, strlen);
	string			line;
	size_t			start = 0;
	size_t			pos;
	content			content;

	while ((pos = input.find("\r\n", start)) != string::npos)
	{
		if (pos + 2== input.size() - 1)
			break ;
		line = input.substr(start, pos - start);
		start = pos + 2;
		stringstream	tmp(line);
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
	for (vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
	{
		if ((*it)->getSock() == sock)
			return (*it);
	}
	return (NULL);
}

Client	*cmd::searchClient(string name)
{
	for (vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
	{
		if ((*it)->getNickname() == name)
			return (*it);
	}
	return (NULL);
}

Channel	*cmd::searchChannel(string channelName)
{
	for (vector<Channel *>::iterator it = _chList.begin(); it != _chList.end(); it++)
		if ((*it)->getChannelName() == channelName)
			return (*it);
	return (NULL);
}

int cmd::parsecommand() {
	int	cnt = 0;
	for (vector<content>::iterator it = _content.begin(); it != _content.end(); it++)
	{
		cout << cnt++ << std::endl;
		if ((*it).cmd == "JOIN")
			join((*it).arg);
		else if ((*it).cmd == "PING")
			ping();
		else if ((*it).cmd == "PRIVMSG")
			privmsg((*it).arg);
		else if ((*it).cmd == "PASS")
			pass((*it).arg);
		else if ((*it).cmd == "NICK")
			nick((*it).arg);
		else if ((*it).cmd == "USER")
			user((*it).arg);
		else if ((*it).cmd == "TOPIC")
			topic((*it).arg);
		else if ((*it).cmd == "QUIT")
			quit((*it).arg);
		else if ((*it).cmd == "MODE")
			mode((*it).arg);
		else if ((*it).cmd == "KICK")
			kick((*it).arg);
		else if ((*it).cmd == "PART")
			part((*it).arg);
		else if ((*it).cmd == "INVITE")
			invite((*it).arg);
	}
	// printCmdVector(*tokens);
	return 0;
}

Channel	*cmd::addChannel(std::string name)
{
	Channel *newChannel = new Channel(name);
	if (!newChannel)
	{
		std::cout << "Error: cmd::addChannel: new Channel()" << std::endl;
		return (NULL);
	}
	_chList.push_back(newChannel);
	return (newChannel);
}

void	cmd::delChannel(Channel *channel)
{
	for (std::vector<Channel *>::iterator it = _chList.begin(); it != _chList.end(); it++)
	{
		if (channel == (*it))
		{
			_chList.erase(it);
			break ;
		}
	}
}

Client	*cmd::addClient(int sock)
{
	Client *newClient = new Client(sock);
	if (!newClient)
	{
		std::cout << "Error: cmd::addClient: new Client()" << std::endl;
		return (NULL);
	}
	_clntList.push_back(newClient);
	return (newClient);
}

void	cmd::delClient(Client *client)
{
	for (std::vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
	{
		if (client == (*it))
		{
			_clntList.erase(it);
			break ;
		}
	}
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
