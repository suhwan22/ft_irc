#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

void	cmd::nick(string nick)
{
	string msg;
	stringstream	ss(nick);
	Client	*me = searchClient(_clntSock); 

	ss >> nick;

	if (!me->getCreated())
	{
		if (!isNickExist(nick))
			me->setIsValidNick(true);
		me->setNickname(nick);
	}
	else if (!me->getIsValidNick())
	{
		if (isNickExist(nick))
		{
			msg = ":irc.local 433 * " + nick + " :Nickname is already in use.\r\n";
			send(_clntSock, msg.c_str(), msg.size(), 0);
		}
		else
		{
			me->setNickname(nick);
			if (me->getPass() != _servPass)
			{
				msg = ":irc.local ";
				//msg = "NOTICE SEOUL :*** Could not resolve your hostname: Request timed out; using your IP address (127.0.0.1) instead.\n";
				msg = msg + "ERROR :Closing link: (" + me->getUserName() + "@127.0.0.1) [Access denied by configuration]\r\n";
				send(_clntSock, msg.c_str(), msg.size(), 0);
			}
			else
			{
				me->setIsValidNick(true);
				msg = ":irc.local 001 " + me->getNickname() + " :Welcome to the Localnet IRC Network " \
					   + me->getNickname() + "!" + me->getUserName() + "@127.0.0.1\r\n";
				send(_clntSock, msg.c_str(), msg.size(), 0);
			}
		}

	}
	else
	{
		if (((!(isalpha(nick[0]))) && nick[0] != '_') || hasSpecialCharacter(nick) || nick.size() > 9)
		{
			msg = ":irc.local 432 " + me->getNickname() + " " + nick + " :Erroneous Nickname\r\n";
			send(_clntSock, msg.c_str(), msg.size(), 0);
			return ;
		}
		else
		{
			vector<Client *>::iterator cliit;
			for(cliit = _clntList.begin(); cliit != _clntList.end(); cliit++) {
				if ((*cliit)->getNickname() == nick) {
					msg = ":irc.local 433 " + me->getNickname() + " " + nick + " :Nickname is already in use.\r\n";
					send(_clntSock, msg.c_str(), msg.size(), 0);
					return ;
				}

			}
			vector<Channel *>::iterator iter;
			for (iter = _chList.begin(); iter != _chList.end(); iter++)
			{
				if ((*iter)->isClientInChannel(me))
				{
					vector<Client *> members = (*iter)->getUsers();
					for (int i = 0; i < (int)members.size(); i++)
					{
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " NICK :" + nick + "\r\n";
						if (members[i]->getSock() != me->getSock())
							send(members[i]->getSock(), msg.c_str(), msg.size(), 0);
						else
							me->setNickname(nick);
							
						
						
					}
				}
			}
			msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " NICK :" + nick + "\r\n";
			send(_clntSock, msg.c_str(), msg.size(), 0);
			else
				me->setNickname(nick);
		}
	}
}

bool	cmd::isNickExist(string nick)
{
	for (vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
		if ((*it)->getNickname() == nick)
			return (true);
	return (false);
}

