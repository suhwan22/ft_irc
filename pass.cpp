#include "cmd.hpp"

void cmd::ping(string arg)
{
	string msg;

	msg = ":" + arg + " PONG " + arg + " :" + arg + "\n";
}
:irc.local PONG irc.local :irc.local