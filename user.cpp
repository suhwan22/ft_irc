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
	client->setCreated(true);
	if (client->getIsValidNick())
	{
		if (client->getPass() != _servPass)
		{
			msg = ":irc.local ";
			//msg = "NOTICE SEOUL :*** Could not resolve your hostname: Request timed out; using your IP address (127.0.0.1) instead.\n";
			msg = msg + "ERROR :Closing link: (" + client->getUserName() + "@127.0.0.1) [Access denied by configuration]\r\n";
			send(_clntSock, msg.c_str(), msg.size(), 0);
		}
		else
		{
			client->setIsValidNick(true);
			msg = ":irc.local 001 " + client->getNickname() + " :Welcome to the Localnet IRC Network " \
				   + client->getNickname() + "!" + client->getUserName() + "@127.0.0.1\r\n";
			send(_clntSock, msg.c_str(), msg.size(), 0);
		}
	}
	else
	{
		msg = ":irc.local 433 * " + me->getNickname() + " " + nick + " :Nickname is already in use.\r\n";
		send(_clntSock, msg.c_str(), msg.size(), 0);
	}
}
