#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

void cmd::ping()
{
	string msg;

	msg = ":irc.local PONG irc.local :irc.local\r\n";
	if (send(_clntSock, msg.c_str(), msg.length(), 0) == -1)
		cerr << "Error: send error" << endl;
	return ;
}