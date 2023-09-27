#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

void cmd::privmsgToChannel(string arg, string inputmsg) {
	vector<Channel *>::iterator	iter;
	string						msg;
	Client 						*me = searchClient(_clntSock);

	for (iter == _chlist.begin(); iter != _chlist.end(); iter++)	{
		if ((*iter)->getChannelName() == arg) {
			vector<Client *> members = (*iter)->getUsers();
			if (!((*iter)->isClientInChannel(me)))
			{
				msg = ":irc.local 404 " + me->getNickname() + " " + arg + " :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.\n";
				if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
					cerr << "Error: send error" << endl;
			}
			else
			{
				for (int i = 0; i < (int)members.size(); i++)
				{
					msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " PRIVMSG " + arg + " " + inputmsg;
					if (send(members[i]->getSock(), msg.c_str(), msg.length(), 0) == -1)
						cerr << "Error: send error" << endl;
				}
			}
			return ;
		}
	}
	noSuchChannel(arg);
}

void cmd::privmsgToClient(string arg, string inputmsg)
{
	vector<Client *>::iterator	iter;
	string						msg;
	Client						*me = searchClient(_clntSock);

	for (iter == _clilist.begin(); iter != _clilist.end(); iter++) {
		if ((*iter)->getNickname() == arg){
			msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " PRIVMSG " + arg + " " + inputmsg;
			if (send((*iter)->getSock(), msg.c_str(), msg.length(), 0) == -1)
				cerr << "Error: send error" << endl;
			return ;
		}
	}
	noSuchNick(arg);
}

void cmd::privmsg(string arg) {
	string line;
	stringstream tmp;
	tmp = stringstream(arg);
	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	line.erase(0, 1);
	if (!isFirstCharacterHash(arg))
		privmsgToChannel(arg, line);
	else
		privmsgToClient(arg, line);
}