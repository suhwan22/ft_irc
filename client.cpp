#include "client.hpp"
#include "channel.hpp"

Client::Client(int clntSock) : _clntSock(clntSock), 
							   _isCreated(false)
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

void	Client::setCreated(const bool val)
{
	_isCreated = val;
}

void	Client::setPort(const int port)
{
	_port = port;
}

void	Client::setIP(const std::string ip)
{
	_ip = ip;
}

void	Client::setPass(const std::string pass)
{
	_pass = pass;
}

void	Client::setNickname(const std::string nickname)
{
	_nickname = nickname;
}

void	Client::setUserName(const std::string userName)
{
	_userName = userName;
}

void	Client::setRealName(const std::string realname)
{
	_realName = realname;
}

const std::string&	Client::getNickname() const
{
	return (_nickname);
}
const std::string&	Client::getUserName() const
{
	return (_userName);
}

const std::string&	Client::getRealName() const
{
	return (_realName);
}

const std::string&	Client::getIP() const
{
	return (_ip);
}

const std::string&	Client::getPass() const
{
	return (_pass);
}

bool	Client::getCreated() const
{
	return (_isCreated);
}

int	Client::getPort() const
{
	return (_port);
}

int	Client::getSock() const
{
	return (_clntSock);
}
