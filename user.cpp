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
		string	msg1 = ":irc.local NOTICE " + client->getNickname() \
						+ " :*** Could not resolve your hostname: Request timed out; " \
						+ "using your IP address (127.0.0.1) instead.\r\n";
		string	msg2 = ":irc.local 002 " + client->getNickname() \
						+ " :Your host is irc.local, running version InspIRCd-3\r\n";
		string	msg3 = ":irc.local 003 " + client->getNickname() \
						+ " :This server was created 18:29:06 Oct 3 2023\r\n";
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
		string	msg7 = ":irc.local 251 JaeyWon :There are 0 users and 0 invisible on 1 servers\r\n";
		string	msg8 = ":irc.local 253 JaeyWon 1 :unknown connections\r\n";
		string	msg9 = ":irc.local 254 JaeyWon 0 :channels formed\r\n";
		string	msg10 = ":irc.local 255 JaeyWon :I have 0 clients and 0 servers\r\n";
		string	msg11 = ":irc.local 265 JaeyWon :Current local users: 0  Max: 4\r\n";
		string	msg12 = ":irc.local 266 JaeyWon :Current global users: 0  Max: 4\r\n";
		string	msg13 = ":irc.local 375 JaeyWon :irc.local message of the day\r\n";
		string	msg14 = ":irc.local 372 JaeyWon : **************************************************\r\n";
		string	msg15 = ":irc.local 372 JaeyWon : *             H    E    L    L    O              *\r\n";
		string	msg16 = ":irc.local 372 JaeyWon : *  This is a private irc server. Please contact  *\r\n";
		string	msg17 = ":irc.local 372 JaeyWon : *  the admin of the server for any questions or  *\r\n";
		string	msg18 = ":irc.local 372 JaeyWon : *  issues.                                       *\r\n";
		string	msg19 = ":irc.local 372 JaeyWon : **************************************************\r\n";
		string	msg20 = ":irc.local 372 JaeyWon : *  The software was provided as a package of     *\r\n";
		string	msg21 = ":irc.local 372 JaeyWon : *  Debian GNU/Linux <https://www.debian.org/>.   *\r\n";
		string	msg22 = ":irc.local 372 JaeyWon : *  However, Debian has no control over this      *\r\n";
		string	msg23 = ":irc.local 372 JaeyWon : *  server.                                       *\r\n";
		string	msg24 = ":irc.local 372 JaeyWon : **************************************************\r\n";
		string	msg25 = ":irc.local 372 JaeyWon : (The sysadmin possibly wants to edit </etc/inspircd/inspircd.motd>)\r\n";
		string	msg26 = ":irc.local 376 JaeyWon :End of message of the day.\r\n";
		client->setCreated(true);
		msg = ":irc.local 001 " + client->getNickname() + " :Welcome to the Localnet IRC Network " \
			   + client->getNickname() + "!" + client->getUserName() + "@127.0.0.1\r\n";
		send(_clntSock, (msg1 + msg + msg2 + msg3 + msg4 + msg5 + msg6 + msg7 + msg8 + msg9 + msg10 + msg11 + msg12 + msg13 \
					+ msg14 + msg15 + msg16 + msg17 + msg18 + msg19 + msg20 + msg21 + msg22 + msg23 + msg24 + msg25 + msg26).c_str(), \
			(msg1 + msg + msg2 + msg3 + msg4 + msg5 + msg6 + msg7 + msg8 + msg9 + msg10 + msg11 + msg12 + msg13 \
					+ msg14 + msg15 + msg16 + msg17 + msg18 + msg19 + msg20 + msg21 + msg22 + msg23 + msg24 + msg25 + msg26).size(), 0);
	}
}
