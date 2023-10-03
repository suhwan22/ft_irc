#include "client.hpp"
#include "channel.hpp"
#include "cmd.hpp"

void	cmd::whois(string nick)
{
	string	mymsg = "", mymsg2 = "";
	string	msg, msg1 = "", msg2, msg3;
	string	idle;
	long long	ltime;
	string	stime = "";
	Client	*me = searchClient(_clntSock);
	Client	*who = searchClient(nick);

	if (nick == me->getNickname())
	{
		mymsg = ":irc.local 378 " + me->getNickname() + " " + nick \
				 + " :is connecting from " + me->getUserName() + "@127.0.0.1 127.0.0.1\r\n";
		mymsg2 = ":irc.local 379 " + me->getNickname() + " " + nick + " :is using modes +i\r\n";
	}
	if (who->getLastJoinChannel())
	{
		msg1 = ":irc.local 319 " + me->getNickname() + " " + nick + " :" + who->getChNames() + "\r\n";
	}

	ltime = time(NULL) - me->getClntTimeLong();
	char	c;

	while (ltime / 10)
	{
		c = '0' + ltime % 10;
		stime.insert(0, 1, c);
		ltime /= 10;
	}
	c = '0' + ltime % 10;
	stime.insert(0, 1 ,c);

	idle = ":irc.local 317 " + me->getNickname() + " " + nick + " " \
			+ stime + " "  + who->getClntTime() + " :seconds idle, signon time\r\n";

	msg = ":irc.local 311 " + me->getNickname() + " " + nick + " " \
		   + who->getUserName() +  " " + who->getIP() + " * :" + who->getRealName() + "\r\n";
	msg2 = ":irc.local 312 " + me->getNickname() + " " + nick + " irc.local :Local IRC Server\r\n";
	msg3 = ":irc.local 318 " + me->getNickname() + " " + nick + " :End of /WHOIS list.\r\n";
	send(_clntSock, (msg + mymsg + msg1 + msg2 + mymsg2 + idle + msg3).c_str(), \
			(msg + mymsg + msg1 + msg2 + mymsg2 + idle + msg3).size(), 0);
}

//:irc.local 311 suhkim suhkim dummy 127.0.0.1 * :DUMMY
//:irc.local 378 suhkim suhkim :is connecting from dummy@127.0.0.1 127.0.0.1
//:irc.local 319 suhkim suhkim :@#456 @#123
//:irc.local 312 suhkim suhkim irc.local :Local IRC Server
//:irc.local 379 suhkim suhkim :is using modes +i
//:irc.local 317 suhkim suhkim 427 1696308741 :seconds idle, signon time
//:irc.local 318 suhkim suhkim :End of /WHOIS list.
