#include "server.hpp"
#include "client.hpp"
#include "channel.hpp"
#include "cmd.hpp"

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

	if (bind(_servSock, (struct sockaddr *) &servAddr, sizeof(servAddr)) == -1)
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
	int	epfd, eventCnt;
	struct epoll_event	*epEvents;
	struct epoll_event	event;

	epfd = epoll_create(EPOLL_SIZE);
	//epEvents = malloc(sizeof(struct epoll_event) * EPOLL_SIZE);
	epEvents = new epoll_event[EPOLL_SIZE];
	event.events = EPOLLIN;
	event.data.fd = _servSock;
	epoll_ctl(epfd, EPOLL_CTL_ADD, _servSock, &event);

	socklen_t	addrSize;
	struct sockaddr_in	clntAddr;
	int	clntSock;

	char	buf[BUF_SIZE];
	int		strlen;
	int		i;

	while (1)
	{
		eventCnt = epoll_wait(epfd, epEvents, EPOLL_SIZE, -1);
		if (eventCnt == -1)
		{
			std::cout << "Error: epoll_wait()" << std::endl;
			break;
		}
		for (i = 0; i < eventCnt; i++)
		{
			if (epEvents[i].data.fd == _servSock)
			{
				/* Add Client!! */
				addrSize = sizeof(clntAddr);
				clntSock = accept(_servSock, (struct sockaddr *)&clntAddr, &addrSize);

				linger optval;
     			optval.l_onoff = 1;
     			optval.l_linger = 1;
				if (setsockopt(clntSock, SOL_SOCKET, SO_LINGER, &optval, sizeof(optval)) == -1)
				{
					std::cout << "Error: serverStart(): setsockopt()" << std::endl;
			        close(clntSock);
			        exit(1);
			    }

				event.events = EPOLLIN;
				event.data.fd = clntSock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clntSock, &event);
				
				addClient(clntSock);
				std::cout << "connected client: " << clntSock << std::endl;
			}
			else
			{
				strlen = recv(epEvents[i].data.fd, buf, BUF_SIZE, 0);
				if (strlen <= 0)
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, epEvents[i].data.fd, NULL);
					delClient(epEvents[i].data.fd);
					std::cout << "closed client: " << epEvents[i].data.fd << std::endl;
					close(epEvents[i].data.fd);
				}
				else
				{
					cmd command(epEvents[i].data.fd, buf, strlen, _passWord, _clntList, _channelList);
					command.printContent(command.getContent());
					command.parsecommand();
				}
				delEmptyChannel();
				for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
				{
					std::vector<Client *> users = (*it)->getUsers();
					std::cout << (*it)->getChannelName() << " : ";
					for (std::vector<Client *>::iterator clnt = users.begin(); clnt != users.end(); clnt++)
						std::cout << (*clnt)->getNickname() << " ";
					std::cout << std::endl;
				}
			}
		}
	}
	close(_servSock);
	close(epfd);
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
			_channelList.erase(it);
			break ;
		}
	}
}

void	Server::delEmptyChannel()
{
	for (std::vector<Channel *>::iterator it = _channelList.begin(); it != _channelList.end(); it++)
		if ((*it)->getUsers().size() == 0)
			_channelList.erase(it);
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

