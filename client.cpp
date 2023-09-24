#include "client.hpp"
#include "channel.hpp"

Client::Client(int ClntSock) : _ClntSock(ClntSock), 
							   _nickname(""), 
							   _userName("")
{
	/* something  */
}

Client::~Client() {}

void	Client::joinChannel(Channel *channel)
{
	for (int i = 0; i < _joinChannels.size(); i++)
	{
		if (_joinChannels[i]->getChannelName()
	}
}
