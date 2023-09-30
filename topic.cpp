#include "cmd.hpp"
#include "channel.hpp"
#include "client.hpp"

void cmd::settingtopic(string arg, string inputmsg) {
	vector<Channel *>::iterator	iter;
	string						topic;
	Client						*me = searchClient(_clntSock);

	for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
		if ((*iter)->getChannelName() == arg) {
			vector<Client *> members = (*iter)->getUsers();
			if (!((*iter)->isClientInChannel(me))) {
				topic = ":irc.local 442 " + me->getNickname() + " " + arg + " :You're not on that channel!\n";
				if (send(_clntSock, topic.c_str(), topic.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				if (!((*iter)->isChennelOp(me))) {
					topic = ":irc.local 482 " + me->getNickname() + " " + arg + " :You do not have access to change the topic on this channel\n";
					if (send(_clntSock, topic.c_str(), topic.size(), 0) == -1)
						cerr << "Error: send error" << endl;
				}
				else {
					for (int i = 0; i < (int)members.size(); i++) {
						topic = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " TOPIC " + arg + " " + inputmsg;
						if (send(members[i]->getSock(), topic.c_str(), topic.size(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
				}
				return ;
			}
		}
	}
	noSuchChannel(arg);
}

void cmd::topic(string arg)
{
	string line;
	stringstream tmp;
	tmp = stringstream(arg);
	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	line.erase(0, 1);
	settingtopic(arg, line);
}