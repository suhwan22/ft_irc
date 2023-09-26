#include "cmd.hpp"

void cmd::privmsgToChannel(vector<string> tokens) {
	vector<Channel *>::iterator 	iter;
	string msg;
	string gotchannel;

	gotchannel = tokens[1];
	for (iter == _chlist.begin(); iter != _chlist.end(); iter++)	{
		if ((*iter)->getChannelName() == gotchannel) {
			
		}
	}
}

void cmd::privmsg(vector<string> tokens) {
	if (tokens[1][0] == '#')
		privmsgToChannel(tokens);
	else
		privmsgToClient(tokens);
}