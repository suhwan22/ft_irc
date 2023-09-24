#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <vector>

class Client;
class Channel;

class Server
{
	private:
		int						_port;
		std::string				_passWord;
		std::vector<Channel *>	_channelList;
		std::vector<Client *>	_clntList;

	public:
		Server(int port, std::string pass);
		~Server();

		//Server& operator=(const Server& obj);

		void	serverInit(int port, std::string pass);
		void	serverStart();

		int	getPort();
		std::string	getPass();

		void	addChannel();
		void	addClient();
};

#endif
