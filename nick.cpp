#include "cmd.hpp"
#include "client.hpp"

void	cmd::nick(string nick)
{
	Client	*client = searchClient(_clntSock);
	if (!client->getCreated())
	{
		/* dup nick check */
//		if (isDupNick(nick))
//			nick += "_";
//		else
			client->setNickname(nick);
	}
	else
	{
		/* normal nick command */
	}
}
