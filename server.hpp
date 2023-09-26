#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <vector>
# include <arpa/inet.h>
# include <sys/epoll.h>

# define BUF_SIZE 100
# define EPOLL_SIZE 50

class Client;
class Channel;

class Server
{
	private:
		int						_servSock;
		int						_port;
		std::string				_passWord;
		std::vector<Channel *>	_channelList;
		std::vector<Client *>	_clntList;

	public:
		Server(int port, std::string pass);
		~Server();

		//Server& operator=(const Server& obj);

		void	serverInit(int port);
		void	serverStart();

		void	addChannel();
		void	addClient();
		void	setClientInfo();

		int		getPort() const;
		const std::string&	getPass() const;

		void	setPass(const std::string pass);
};

#endif
