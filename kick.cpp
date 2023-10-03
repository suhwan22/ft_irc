#include "cmd.hpp"
#include "channel.hpp"
#include "client.hpp"

void cmd::execKick(string ch_name, string nick)
{
	string						msg;
	string 						inputmsg;
	stringstream 				tmp(nick);
	vector<Channel *>::iterator	chiter;
	vector<Client *>::iterator	cliter;
	Client						*me = searchClient(_clntSock);

	tmp >> nick;
	getline(tmp, inputmsg, static_cast<char>(EOF));
	inputmsg.erase(0, 1);

	for (cliter = _clntList.begin(); cliter != _clntList.end(); cliter++) {
		if ((*cliter)->getNickname() == nick) {
			for (chiter = _chList.begin(); chiter != _chList.end(); chiter++) {
				if ((*chiter)->getChannelName() == ch_name) {
					vector<Client *> members = (*chiter)->getUsers();
					if (!(*chiter)->isClientOp(me)) {
						msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + " :You must be a channel operator\r\n";
						if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
						return; 
					}
					else {
						for (int i = 0; i < (int)members.size(); i++) {
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " KICK " + ch_name + " " + nick + " " + inputmsg + "\r\n";
							if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cout << "Error: send error" << endl; 
						}
						(*chiter)->delUser(*cliter);
						(*cliter)->exitChannel(ch_name);
					}
					return ;
				}
			}
			noSuchChannel(ch_name);
		}
	}
	noSuchNick(nick);
}

void cmd::kick(string arg)
{
	string line;
	stringstream tmp(arg);

	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	line.erase(0, 1);
	execKick(arg, line);
}
