#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"
#include "cmd.hpp"
#include <fcntl.h>

Server::Server(int port, std::string pass) : _port(port), _passWord(pass) {}

Server::~Server() {}

void	Server::serverInit()
{
	struct sockaddr_in	servAddr;

	_servSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(_port);

	int flags = fcntl(_servSock, F_GETFL, 0);
	fcntl(_servSock, F_SETFL, flags | O_NONBLOCK);

	if (bind(_servSock, (struct sockaddr *)&servAddr, sizeof(servAddr)) == -1)
	{
		std::cout << "Error: bind()" << std::endl;
		exit(1);
	}

	if (listen(_servSock, 5) == -1)
	{
		std::cout << "Error: listen()" << std::endl;
		exit(1);
	}
}

void	Server::serverStart()
{
	int		eventCnt, flags;
	socklen_t	addrSize;
	struct sockaddr_in	clntAddr;
	int	clntSock;

	char	buf[BUF_SIZE];
	int		strlen;
	int		i;

	int kq = kqueue();
	if (kq < 0) {
		std::cerr << "Failef to create kqueue" << std::endl;
		close(_servSock);
		return ;
	}

	struct kevent events[10];
	struct kevent change;

	EV_SET(&change, _servSock, EVFILT_READ, EV_ADD, 0, 0, NULL);

	if (kevent(kq, &change, 1, NULL, 0, NULL) < 0) {
		std::cerr << "Failed to register server socket with kqueue" << std::endl;
		close(_servSock);
		close(kq);
		return ;
	}

	while (1)
	{
		eventCnt = kevent(kq, NULL, 0, events, 10, NULL);

		if (eventCnt == -1)
		{
			std::cout << "Error: epoll_wait()" << std::endl;
			break;
		}
		for (i = 0; i < eventCnt; i++)
		{
			if ((int)events[i].ident == _servSock)
			{
				/* Add Client!! */
				clntSock = accept(_servSock, (struct sockaddr *)&clntAddr, &addrSize);

				flags = fcntl(clntSock, F_GETFL, 0);
				fcntl(clntSock, F_SETFL, flags | O_NONBLOCK);
				EV_SET(&change, clntSock, EVFILT_READ, EV_ADD, 0, 0, NULL);
				if (kevent(kq, &change, 1, NULL, 0, NULL) < 0) {
					std::cerr << "Failed to register client socket with kqueue" << std::endl;
					close(clntSock);
				}

				/* linger socket */
				linger optval;
     			optval.l_onoff = 1;
     			optval.l_linger = 1;
				if (setsockopt(clntSock, SOL_SOCKET, SO_LINGER, &optval, sizeof(optval)) == -1)
				{
					std::cout << "Error: serverStart(): setsockopt()" << std::endl;
			        close(clntSock);
			        exit(1);
			    }
				
				addClient(clntSock);
				std::cout << "connected client: " << clntSock << std::endl;
			}
			else
			{
				strlen = recv(events[i].ident, buf, BUF_SIZE, 0);
				if (strlen <= 0)
				{
					EV_SET(&change, events[i].ident, EVFILT_READ, EV_DELETE, 0, 0, NULL);
					delClient(events[i].ident);
					std::cout << "closed client: " << events[i].ident << std::endl;
					close(events[i].ident);
				}
				else
				{
					cmd command(events[i].ident, buf, strlen, _passWord, _clntList, _channelList);
					command.printContent(command.getContent());
					command.parsecommand();
				}
				std::cout << "current user(" << _clntList.size() << ") : ";
				for (std::vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
					std::cout << (*it)->getNickname() << " ";
				std::cout << std::endl;

				std::cout << "current each user Channels" << std::endl;
				for (std::vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
				{
					std::cout << (*it)->getNickname() << " : ";
					(*it)->printJoinChannel();
					std::cout << std::endl;
				}

				std::cout << "\ncurrent channel(" << _channelList.size() << ") : ";
				for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
					std::cout << (*it)->getChannelName() << " ";
				std::cout << std::endl;

				std::cout << "current each channel user" << std::endl;
				for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
				{
					std::cout << (*it)->getChannelName() << std::endl;
					(*it)->printUsers();
					(*it)->printOpUsers();
					(*it)->printInviteUsers();
					std::cout << std::endl;
				}
			}
		}
	}
	close(_servSock);
	close(kq);
}

void	Server::addChannel(std::string name)
{
	Channel *newChannel = new Channel(name);
	if (!newChannel)
	{
		std::cout << "Error: Server::addChannel: new Channel()" << std::endl;
	}
	_channelList.push_back(newChannel);
}

void	Server::delChannel(Channel *channel)
{
	for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
	{
		if (channel == (*it))
		{
			if (_channelList.size() == 1)
			{
				_channelList.erase(it);
				_channelList = std::vector<Channel *>();
			}
			else
				_channelList.erase(it);
			break ;
		}
	}
}

void	Server::addClient(int sock)
{
	Client *newClient = new Client(sock);
	if (!newClient)
	{
		std::cout << "Error: Server::addClient: new Client()" << std::endl;
	}
	_clntList.push_back(newClient);
}

void	Server::delClient(Client *client)
{
	for (std::vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
	{
		if (client == (*it))
		{
			if (_clntList.size() == 1)
			{
				_clntList.erase(it);
				_clntList = std::vector<Client *>();
			}
			else
				_clntList.erase(it);
			break ;
		}
	}
}

void	Server::delClient(int sock)
{
	for (std::vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
	{
		if (sock == (*it)->getSock())
		{
			if (_clntList.size() == 1)
			{
				_clntList.erase(it);
				_clntList = std::vector<Client *>();
			}
			else
				_clntList.erase(it);
			break ;
		}
	}
}

int	Server::getSock() const
{
	return (_servSock);
}

int	Server::getPort() const
{
	return (_port);
}

const std::string&	Server::getPass() const
{
	return (_passWord);
}

