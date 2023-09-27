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
		int						_clntSock;

		/* 아이피랑 포트 어떤식으로 들어오는지 봐야함 */
		std::string				_ip;
		int						_port;

		/* user information */
		bool					_isCreated;
		std::string				_pass;
		std::string				_nickname;
		std::string				_realName;
		std::string				_userName;
		std::vector<Channel *>	_joinChannels;

	public:
		Client(int ClntSock);
		~Client();

		void	joinChannel(Channel *channel);
		void	exitChannel(const std::string channelName);
		void	cleanChannel();

		/* setter func */
		void	setCreated(const bool val);
		void	setPort(const int port);
		void	setIP(const std::string ip);
		void	setPass(const std::string pass);
		void	setNickname(const std::string nickname);
		void	setRealName(const std::string realname);
		void	setUserName(const std::string userName);
		
		/* getter func */
		const std::string&	getNickname() const;
		const std::string&	getUserName() const;
		const std::string&	getRealName() const;
		const std::string&	getIP() const;
		const std::string&	getPass() const;
		bool				getCreated() const;
		int					getSock() const;
		int					getPort() const;
};

#endif
