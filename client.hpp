#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <string>
# include <vector>

class Channel;

class Client
{
	private:
		/* client socket info */
		int			_ClntSock;
		/* 아이피랑 포트 어떤식으로 들어오는지 봐야함 */
		std::string	_ip;
		int			_port;

		/* user information */
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
		
		const std::string&	getNickname() const;
		const std::string&	getUserName() const;
		const std::string&	getIP() const;
		int					getSock() const;
};

#endif
