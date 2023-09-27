#include "cmd.hpp"
#include "client.hpp"

void	cmd::user(string arg)
{
	Client	*client = searchClient(_clntSock);
	stringstream	temp(arg);
	string			realname;
	string			username;
	string			ip;

	temp >> username;
	temp >> username;
	temp >> ip;
	temp >> realname;
	realname.erase(0, 1);

	client->setRealName(realname);
	client->setUserName(username);
	client->setIP(ip);
	if (client->getPass() != _servPass)
	{
		string	msg;

		msg = "ERROR :Closing link: (" + client->getUserName() + "@" + client->getIP() + ") [Access denied by configuration]\n";
		send(_clntSock, msg.c_str(), msg.size() - 1, 0);
	}
	else
		client->setCreated(true);
}
