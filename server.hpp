#ifndef SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <string>
# include <vector>

class Server
{
	private:
		int		_port;
		std::string	_passWord;
		std::vector<Channel *>	channelList;
		std::vector<Client *>	clntList;

	public:
		Server();
		Server(int port, std::string pass);
		Server(const Server& obj);
		~Server();

		Server& operator=(const Server& obj);

		void	serverInit(int port, std::string pass);
		void	serverStart();

		int	getPort();
		std::string	getPass();

		void	addChannel();
		void	addClient();
};

#endif
