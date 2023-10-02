#include "channel.hpp"
#include "client.hpp"

Channel::Channel(std::string channelName) :
	_channelName(channelName),
	_passWord(""),
	_userLimit(2147483647), _kflag(false), _iflag(false), _tflag(true), _lflag(false), _isEmpty(false)
{}

Channel::Channel(std::string channelName, std::string password) :
	_channelName(channelName),
	_passWord(password),
	_userLimit(2147483647), _kflag(false), _iflag(false), _tflag(true), _lflag(false), _isEmpty(false)
{}

Channel::~Channel() {}

void	Channel::addUser(Client *client)
{
	for (std::vector<Client *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (client == *(it))
			return ;
	}
	_users.push_back(client);
}

void	Channel::delUser(Client *client)
{
	for (std::vector<Client *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if ((*it) == client)
		{
			_users.erase(it);
			break ;
		}
	}
}

bool	Channel::isClientInChannel(Client *client)
{
	for (std::vector<Client *>::iterator it = _users.begin(); it != _users.end(); it++)
		if ((*it) == client)
			return (true);
	return (false);
}

void	Channel::addOpUser(Client *client)
{
	for (std::vector<Client *>::iterator it = _opUsers.begin(); it != _opUsers.end(); it++)
	{
		if (client == *(it))
			return ;
	}
	_opUsers.push_back(client);
}

void	Channel::delOpUser(Client *client)
{
	for (std::vector<Client *>::iterator it = _opUsers.begin(); it != _opUsers.end(); it++)
	{
		if ((*it) == client)
		{
			_opUsers.erase(it);
			break ;
		}
	}
}

bool	Channel::isClientOp(Client *client)
{
	for (std::vector<Client *>::iterator it = _opUsers.begin(); it != _opUsers.end(); it++)
		if ((*it) == client)
			return (true);
	return (false);
}

void	Channel::addInviteUser(Client *client)
{
	for (std::vector<Client *>::iterator it = _inviteUsers.begin(); it != _inviteUsers.end(); it++)
	{
		if (client == *(it))
			return ;
	}
	_inviteUsers.push_back(client);
	
}

void	Channel::delInviteUser(Client *client)
{
	for (std::vector<Client *>::iterator it = _inviteUsers.begin(); it != _inviteUsers.end(); it++)
	{
		if ((*it) == client)
		{
			_inviteUsers.erase(it);
			break ;
		}
	}
}

bool	Channel::isClientInvite(Client *client)
{
	for (std::vector<Client *>::iterator it = _inviteUsers.begin(); it != _inviteUsers.end(); it++)
		if ((*it) == client)
			return (true);
	return (false);
}

void	Channel::setInviteOnlyFlag(const bool flag)
{
	_iflag = flag;
}

void	Channel::setChPassFlag(const bool flag)
{
	_kflag = flag;
}

void	Channel::setChTopicFlag(const bool flag)
{
	_tflag = flag;
}

void	Channel::setChLimitFlag(const bool flag)
{
	_lflag = flag;
}

void	Channel::setIsEmpty(const bool flag)
{
	_isEmpty = flag;
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

std::string	Channel::getUsersName()
{
	std::string	users = "";

	for (std::vector<Client *>::iterator it = _users.begin(); it != _users.end(); it++)
	{
		if (isClientOp((*it)))
			users += "@" + ((*it)->getNickname() + " ");
		else
			users += ((*it)->getNickname() + " ");
	}
	users.erase(users.size() - 1, 1);
	return (users);
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

const std::vector<Client *>&	Channel::getUsers() const
{
	return (_users);
}

bool Channel::getInviteOnlyFlag() const
{
	return (_iflag);
}
bool Channel::getChPassFlag() const
{
	return (_kflag);
}
bool Channel::getChTopicFlag() const
{
	return (_tflag);
}

bool Channel::getChLimitFlag() const
{
	return (_lflag);
}

bool	Channel::getIsEmpty() const
{
	return (_isEmpty);
}
