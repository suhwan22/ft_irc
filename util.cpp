#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"


void cmd::noSuchNick(string wrongnick) {
	string	msg;
	Client	*me = searchClient(_clntSock);

	msg = ":irc.local 401 " + me->getNickname() + " " + wrongnick + " :No such nick\n";
	if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
		cerr << "Error: send err" << endl;
}

void cmd::noSuchChannel(string wrongchannel) {
	string	msg;
	Client	*me = searchClient(_clntSock);

	
	msg = ":irc.local 403 " + me->getNickname() + " " + wrongchannel + " :No such channel\n";
	if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
		cerr << "Error: send err" << endl;
}

bool cmd::hasSpecialCharacter(const std::string& str) {
    std::string specialCharacters = "!@#$%^&*()+-=[]{}|;:'\",.<>?";

    size_t found = str.find_first_of(specialCharacters);
    return found != std::string::npos;
}

void cmd::sendNotOpMsg(string channel, string mode, bool flag)
{
	string	msg;
	Client	*me = searchClient(_clntSock);
	if (flag == true)
	{
		msg = ":irc.local 482 " + me->getNickname() + " " + channel + \
			" :You must have channel op access or above to set channel mode " + mode + "\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
	}
	else if (flag == true)
	{
		msg = ":irc.local 482 " + me->getNickname() + " " + channel + \
			" :You must have channel op access or above to unset channel mode " + mode + "\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
	}
}