#include "client.hpp"
#include "channel.hpp"
#include <cstdlib>
#include "content.hpp"
#include <sstream>

Client::Client(int clntSock) : _clntSock(clntSock), 
							   _isCreated(false),
							   _isValidNick(false),
							   _clntTime(saveTime()),
							   _clntTimeLong(std::strtod(_clntTime.c_str(), NULL))
{}

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
			if (_joinChannels.size() == 1)
			{
				_joinChannels.erase(it);
				_joinChannels = std::vector<Channel *>();
			}
			else
				_joinChannels.erase(it);
			return ;
		} }
}

void	Client::recv(char *buf, int len, std::vector<Content>& contentList)
{
	std::string	str(buf, len);
	std::string	line, cmd;
	size_t	start = 0, pos;

	_input += str;
	while ((pos = _input.find("\r\n", start)) != std::string::npos)
	{
		line = _input.substr(start, pos - start);
		start = pos + 2;
		std::stringstream	tmp(line);
		tmp >> line;
		cmd = line;
		if (!tmp.eof())
		{
			getline(tmp, line, static_cast<char>(EOF));
			line.erase(0, 1);
		}
		else
			line = "";
		Content	content(cmd, line);
		if (pos + 2 == _input.size() - 1)
			break ;
	}
}

void	Client::cleanChannel()
{
	_joinChannels.clear();
}

void	Client::printJoinChannel()
{
	for (std::vector<Channel *>::iterator it = _joinChannels.begin(); it != _joinChannels.end(); it++)
		std::cout << (*it)->getChannelName() << " ";
	std::cout << std::endl;
}

std::string	Client::saveTime()
{
	long long	ltime = static_cast<long long>(time(NULL));
	std::string stime = "";
	char	c;

	while (ltime / 10)
	{
		c = '0' + ltime % 10;
		stime.insert(0, 1, c);
		ltime /= 10;
	}
	c = '0' + ltime % 10;
	stime.insert(0, 1 ,c);
	return stime;
}

void	Client::setCreated(const bool val)
{
	_isCreated = val;
}

void	Client::setIsValidNick(const bool val)
{
	_isValidNick = val;
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

Channel*	Client::getLastJoinChannel() const
{
	if (_joinChannels.empty())
		return (NULL);
	return (_joinChannels[_joinChannels.size() - 1]);
}

std::string	Client::getChNames()
{
	std::string	chnames = "";

	if (_joinChannels.size() == 0)
		return (chnames);
	for (std::vector<Channel *>::iterator it = _joinChannels.begin(); it != _joinChannels.end(); it++)
	{
		if ((*it)->isClientOp(this))
			chnames += "@";
		chnames += (*it)->getChannelName();
		chnames += " ";
	}
	chnames.erase(chnames.size() - 1, 1);
	return (chnames);
}

const std::string&	Client::getClntTime() const
{
	return (_clntTime);
}

bool	Client::getCreated() const
{
	return (_isCreated);
}

bool	Client::getIsValidNick() const
{
	return (_isValidNick);
}

int	Client::getSock() const
{
	return (_clntSock);
}

long long	Client::getClntTimeLong() const
{
	return (_clntTimeLong);
}
