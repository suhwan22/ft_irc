#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

void	cmd::nick(string nick)
{
	string msg;
	Client	*me = searchClient(_clntSock); 
	if (!me->getCreated())
	{
		/* dup nick check */
		if (isNickExist(nick))
			nick += "_";
		me->setNickname(nick);
	}
	else
	{
		if (((!(isalpha(nick[0]))) && nick[0] != '_') || hasSpecialCharacter(nick) || nick.size() > 9)
		{
			msg = ":irc.local 432 " + me->getNickname() + " " + nick + " :Erroneous Nickname\r\n";
			if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
				cerr << "Error: send error" << endl;
			return ;
		}
		else
		{
			vector<Client *>::iterator cliit;
			for(cliit = _clntList.begin(); cliit != _clntList.end(); cliit++) {
				if ((*cliit)->getNickname() == nick) {
					msg = ":irc.local 433 " + me->getNickname() + " " + nick + " :Nickname is already in use.\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << std::endl;
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
						if (members[i]->getSock() != me->getSock() && \
						 send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
						else
							me->setNickname(nick);
							
						
						
					}
				}
			}
			msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " NICK :" + nick + "\r\n";
			if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
				cerr << "Error: send error" << endl;
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

