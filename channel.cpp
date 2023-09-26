#include "channel.hpp"

Channel::Channel(std::string channelName) :
	_channelName(channelName),
	_passWord(""),
	_userLimit(2147483647)
{}

Channel::Channel(std::string channelName, std::string password) :
	_channelName(channelName),
	_passWord(password),
	_userLimit(2147483647)
{}

Channel::~Channel() {}

void	Channel::setPassWord(const std::string passWord)
{
	_passWord = passWord;
}

void	Channel::setUserLimit(const int limit)
{
	_userLimit = limit;
}

const std::string&	Channel::getChannelName() const
{
	return (_channelName);
}

const std::string&	Channel::getPassWord() const
{
	return (_passWord);
}

const int	Channel::getUserLimit() const
{
	return (_userLimit);
}
