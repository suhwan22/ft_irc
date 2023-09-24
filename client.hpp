#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <vector>

class Channel;

class Client
{
	private:
		int			_ClntSock;
		std::string	_nickname;
		std::string	_userName;
		std::vector<Channel *>	_joinChannels;

	public:
		Client(int ClntSock);
		~Client();

		void	joinChannel(Channel *channel);
		void	exitChannel(const std::string channelName);
		void	cleanChannel();

		void	setNickname(const std::string nickname);
		void	setUserName(const std::string userName);
		
		const std::string& getNickname() const;
		const std::string& getUserName() const;
};

#endif
