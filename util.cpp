#include "cmd.hpp"

void cmd::noSuchNick(string wrongnick) {
	string	msg;
	Client	*me = searchClient(_clntSock);

	msg = ":irc.local 401 " + me.getNickname() + wrongnick + ":No such nick\n";
	if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
		cerr << "Error: send err" << endl;
}

void cmd::noSuchChannel(string wrongchannel) {
	string	msg;
	Client	*me = searchClient(_clntSock);

	msg = ":irc.local 403 " + me.getNickname() + wrongchannel + ":No such channel\n";
	if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
		cerr << "Error: send err" << endl;
}

bool cmd::isFirstCharacterHash(const std::string& str) {
    if (!str.empty() && str[0] == '#') {
        return true;
    } else {
        return false;
    }
}