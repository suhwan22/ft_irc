#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <iostream>
# include <cstdio>
# include <string>
# include <vector>

class Channel;

class Client
{
	private:
		/* client socket info */
		int						_clntSock;

		/* 아이피  어떤식으로 들어오는지 봐야함 -> 들어오는 ip는 서버 ip였다,, */
		/* 실제로 client의 ip는 없고 서버가 할당해준다 host name을 못찾아서? 인듯 */
		std::string				_ip;

		/* user init stat */
		bool					_isCreated;
		bool					_isValidNick;

		/* user information */
		std::string				_pass;
		std::string				_nickname;
		std::string				_realName;
		std::string				_userName;
		std::vector<Channel *>	_joinChannels;

	public:
		Client(int ClntSock);
		~Client();

		/* Channel func */
		void	joinChannel(Channel *channel);
		void	exitChannel(const std::string channelName);
		void	cleanChannel();

		/* setter func */
		void	setCreated(const bool val);
		void	setIsValidNick(const bool val);
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
		Channel*			getLastJoinChannel() const;
		bool				getCreated() const;
		bool				getIsValidNick() const;
		int					getSock() const;

		/* print func */
		void	printJoinChannel();
};

#endif
