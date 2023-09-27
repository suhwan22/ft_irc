#include "cmd.hpp"

void cmd::privmsgToChannel(vector<string> tokens, string inputmsg) {
	vector<Channel *>::iterator	iter;
	string						msg;
	string 						gotchannel;
	Client 						*me = serachClient(_clntSock);

	gotchannel = tokens[1];
	for (iter == _chlist.begin(); iter != _chlist.end(); iter++)	{
		if ((*iter)->getChannelName() == gotchannel) {
			vector<Client *> members = (*iter)->getclientlist();
			if (!((*iter)->amimember(_clntSock)))
			{
				msg = ":irc.local 404 " + me->getNickname() + " " + gotchannel + " :You cannot send external messages to this channel whilst the +n (noextmsg) mode is set.\n";
				if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
					cerr << "Error: send error" << endl;
			}
			else
			{
				for (int i = 0; i < (int)members.size(); i++)
				{
					msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP + " PRIVMSG " + gotchannel + " " + inputmsg;
					if (send(members[i]->getSock, msg.c_str(), msg.length(), 0) == -1)
						cerr << "Error: send error" << endl;
				}
			}
			return ;
		}
	}
	noSuchChannel(gotchannel);
}

void cmd::privmsgToClient(vector<string> tokens, string inputmsg)
{
	vector<Client *>::iterator	iter;
	string						msg;
	string						gotclient;
	Client						*me = serachClient(_clntSock);

	gotclient = tokens[1];
	for (iter == _clilist.begin(); iter != _clilist.end(); iter++) {
		if ((*iter)->getNickname() == gotclient){
			msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " PRIVMSG " + gotclient + " " + inputmsg;
			if (send((*iter)->getSock(), msg.c_str(), msg.length(), 0) == -1)
				cerr << "Error: send error" << endl;
			return ;
		}
	}
	noSuchNick(gotclient);
}

void cmd::privmsg(string arg) {
	string line;
	stringstream tmp;
	if (!isFirstCharacterHash(arg))
		privmsgToChannel(tokens);
	tmp = stringstream(arg);
	tmp >> arg;
	getline(tmp, arg, static_cast<char>(EOF));
	arg.erase(0, 1);
	else
		privmsgToClient(tokens);
}