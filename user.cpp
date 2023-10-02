#include "cmd.hpp"
#include "client.hpp"

void	cmd::user(string arg)
{
	Client	*client = searchClient(_clntSock);
	stringstream	temp(arg);
	string			realname;
	string			username;
	string			ip;
	string			msg;

	temp >> username;
	temp >> username;
	temp >> ip;
	temp >> realname;
	realname.erase(0, 1);

	client->setRealName(realname);
	client->setUserName(username);
	client->setIP(ip);
	if (client->getPass() != _servPass)
	{
		msg = ":irc.local ";
		//msg = "NOTICE SEOUL :*** Could not resolve your hostname: Request timed out; using your IP address (127.0.0.1) instead.\n";
		msg = msg + "ERROR :Closing link: (" + client->getUserName() + "@127.0.0.1) [Access denied by configuration]\r\n";
		send(_clntSock, msg.c_str(), msg.size(), 0);
	}
	else
	{
		string	msg2 = ":irc.local 002 " + client->getNickname() \
						+ " :Your host is irc.local, running version InspIRCd-3\r\n";
		string	msg3 = ":irc.local 003 " + client->getNickname() \
						+ " :This server was created 09:53:06 Sep 30 2023\r\n";
		string	msg4 = ":irc.local 004 " + client->getNickname() \
						+ " irc.local ircserv iosw biklmnopstv :bklov\r\n";
		string	msg5 = ":irc.local 005 " + client->getNickname() \
						+ " AWAYLEN=200 CASEMAPPING=rfc2813 CHANLIMIT=#:20 " \
						+ "CHANMODES=b,k,l,imnpst CHANNELLEN=50 CHANTYPES=# ELIST=CMNTU " \
						+ "HOSTLEN=64 KEYLEN=32 KICKLEN=255 LINELEN=512 MAXLIST=b:100 " \
						+ ":are supported by this server\r\n";
		string	msg6 = ":irc.local 005 " + client->getNickname() \
						+ " MAXTARGETS=20 MODES=20 NAMELEN=128 NETWORK=Localnet NICKLEN=20 " \
						+ "PREFIX=(ov)@+ SAFELIST STATUSMSG=@+ TOPICLEN=307 USERLEN=10 " \
						+ "USERMODES=,,s,iow WHOX :are supported by this server\r\n";
		client->setCreated(true);
		msg = ":irc.local 001 " + client->getNickname() + " :Welcome to the Localnet IRC Network " \
			   + client->getNickname() + "!" + client->getUserName() + "@127.0.0.1\r\n";
		send(_clntSock, (msg + msg2 + msg3 + msg4 + msg5 + msg6).c_str(), \
				(msg + msg2 + msg3 + msg4 + msg5 + msg6).size(), 0);
	}
}
