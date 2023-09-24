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

		int						userLimit;

	public:
		Channel(std::string channelName);
		~Channel();

		void	setPassWord(const std::string passWord);
		void	setUserLimit(const int limit);

		const std::string&	getChannelName();
		const std::string&	getPassWord();
		const int			getUserLimit();
		
};

#endif
