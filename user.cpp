#include "cmd.hpp"
#include "client.hpp"

void	cmd::user(string arg)
{
	Client	*client = searchClient(_clntSock);
	stringstream	temp(arg);
	string			realname;
	string			username;
	string			ip;
	string			msg;

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
		msg = ":irc.local ";
		//msg = "NOTICE SEOUL :*** Could not resolve your hostname: Request timed out; using your IP address (127.0.0.1) instead.\n";
		msg = msg + "ERROR :Closing link: (" + client->getUserName() + "@" + client->getIP() + ") [Access denied by configuration]\n";
		send(_clntSock, msg.c_str(), msg.size(), 0);
	}
	else
	{
		client->setCreated(true);
		msg = ":irc.local 001 jaeywon :Welcome to the Localnet IRC Network jaeywon!jaeywon@127.0.0.1\n";
		send(_clntSock, msg.c_str(), msg.size(), 0);
	}
}
