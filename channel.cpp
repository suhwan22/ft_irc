#include "channel.hpp"
#include "client.hpp"

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

bool	Channel::isClientInChannel(Client *client)
{
	for (std::vector<Client *>::iterator it = _users.begin(); it != _users.end(); it++)
		if ((*it)->getNickname() == client->getNickname())
			return (true);
	return (false);
}

void	Channel::setPassWord(const std::string passWord)
{
	_passWord = passWord;
}

void	Channel::setUserLimit(const int limit)
{
	_userLimit = limit;
}

void	Channel::setTopic(const std::string topic)
{
	_topic = topic;
}

const std::string&	Channel::getChannelName() const
{
	return (_channelName);
}

const std::string&	Channel::getPassWord() const
{
	return (_passWord);
}

int	Channel::getUserLimit() const
{
	return (_userLimit);
}

const std::vector<Client *>	Channel::getUsers() const
{
	return (_users);
}
