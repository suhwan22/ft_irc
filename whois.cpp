#include "client.hpp"
#include "channel.hpp"
#include "cmd.hpp"

void	cmd::whois(string nick)
{
	string	msg;
	Client	*me = searchClient(_clntSock);
	// Client	*who = searchClient(nick);

	msg = ":irc.local 311 " + me->getNickname() + " " + nick + " " + me->getUserName() +  " " + me->getIP() + " * :" + me->getUserName() + "\r\n" + \
	":irc.local 319 " + me->getNickname() + " " + nick + " :#123\r\n" + \ 
	":irc.local 312 " + me->getNickname() + " " + nick + " irc.local :Local IRC Server\r\n" + \
	":irc.local 318 " + me->getNickname() + " " + nick + " :End of /WHOIS list.\r\n";
	send(_clntSock, msg.c_str(), msg.size(), 0);
}

// :irc.local 311 test2 test root 127.0.0.1 * :root
// :irc.local 319 test2 test :#123
// :irc.local 312 test2 test irc.local :Local IRC Server
// :irc.local 317 test2 test 873 1696305780 :seconds idle, signon time
// :irc.local 318 test2 test :End of /WHOIS list.

