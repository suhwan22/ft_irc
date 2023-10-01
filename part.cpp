#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

void cmd::execPart(string ch_name, string inputmsg)
{
	vector<Channel *>::iterator	iter;
	string						msg;
	Client						*me = searchClient(_clntSock);

	for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
		if ((*iter)->getChannelName() == ch_name) {
			vector<Client *> members = (*iter)->getUsers();
			if (!((*iter)->isClientInChannel(me))) {
				msg = ":irc.local 442 " + me->getNickname() + " " + ch_name + " :You're not on that channel!\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				for (int i = 0; i < (int)members.size(); i++){
					msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " PART " + ch_name + " :" + inputmsg + "\r\n";
					if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					
				}
				(*iter)->delUser(me);
			}
			return ;
		}
	}
	noSuchChannel(ch_name);
}

void cmd::part(string arg)
{
	string line;
	stringstream tmp;
	tmp = stringstream(arg);
	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	line.erase(0, 1);
	execPart(arg, line);
}