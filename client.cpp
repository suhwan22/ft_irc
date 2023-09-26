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
	for (std::vector<Channel *>::iterator it = _joinChannels.begin(); it != _joinChannels.end(); it++)
	{
		if ((*it)->getChannelName() == channel->getChannelName())
			return ;
	}
	_joinChannels.push_back(channel);
}

void	Client::exitChannel(const std::string channelName)
{
	for (std::vector<Channel *>::iterator it = _joinChannels.begin(); it != _joinChannels.end(); it++)
	{
		if ((*it)->getChannelName() == channelName)
		{
			_joinChannels.erase(it);
			return ;
		}
	}
}

void	Client::cleanChannel()
{
	/* 그냥 써도 되나? */
	_joinChannels.clear();
}

void	Client::setNickname(const std::string nickname)
{
	_nickname = nickname;
}

void	Client::setUserName(const std::string userName)
{
	_userName = userName;
}

const std::string&	Client::getNickname() const
{
	return (_nickname);
}
const std::string&	Client::getUserName() const
{
	return (_userName);
}

const std::string&	Client::getIP() const
{
	return (_ip);
}

int	Client::getSock() const
{
	return (_port);
}
