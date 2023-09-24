#include "server.hpp"

Server::Server(int port, std::string pass) : _port(port), _passWord(pass) {}

Server::~Server() {}

void	addChannel(std::string name)
{
	_channelList.pushback(Channel(name));
}

void	addClient(std::string nickname)
{
	_clntList.pushback(Client(nickname));
}
