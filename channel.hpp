#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>

class Client;

class Channel
{
	private:
		std::string				_channelName;
		std::string				_passWord;
		std::vector<Client *>	_users;

		int						_userLimit;

	public:
		Channel(std::string channelName);
		Channel(std::string channelName, std::string password);
		~Channel();

		bool	isClientInChannel(Client *client);

		void	setPassWord(const std::string passWord);
		void	setUserLimit(const int limit);

		const std::string&	getChannelName() const;
		const std::string&	getPassWord() const;
		const int			getUserLimit() const;
		const std::vector<Client *>	getUsers() const;
};

#endif
