#include "server.hpp"

Server::Server(int port, std::string pass) : _port(port), _passWord(pass) {}

Server::~Server() {}

void	Server::serverInit(int port)
{
	struct sockaddr_in	servAddr;

	_servSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAddr, 0, sizeof(servAddr));
	servAddr.sin_family = AF_INET;
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servAddr.sin_port = htons(port);

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
				event.events = EPOLLIN;
				event.data.fd = clntSock;
				epoll_ctl(epfd, EPOLL_CTL_ADD, clntSock, &event);
				
				addClient(clntSock);
				std::cout << "connected client: " << (_clntList.at(_clntList.size()))->getSock() << std::endl;
			}
			else
			{
				strlen = recv(epEvents[i].data.fd, buf, BUF_SIZE, 0);
				if (strlen == -1)
				{
					std::cout << "Error: serverStart(): recv()" << std::endl;
				}

				std::string receivedstring(buf, strlen);
				char *str = strtok((char *)receivedstring.c_str(), " ");
				std::vector<std::string> _cmd;
				while (str != NULL)
				{
				//	std::cout << "1" << std::endl;
					_cmd.push_back(std::string(str));
					str = strtok(NULL, "");
				}

				std::cout << "CMD= " << _cmd[0] << std::endl;
				//for (auto it = _cmd.begin(); it != _cmd.end(); ++it) {
				//	std::cout << *it << std::endl;
				//}
				if (strlen == 0)
				{
					epoll_ctl(epfd, EPOLL_CTL_DEL, epEvents[i].data.fd, NULL);
					std::cout << "closed client: " << epEvents[i].data.fd << std::endl;
					shutdown(epEvents[i].data.fd, SHUT_RDWR);
				}
				else
				{
					if (strstr(buf, "USER"))
					{
						send(clntSock, ":irc.local 001 suhkim :Welcome to the Localnet IRC Network suhkim!root@127.0.0.1\n", \
								sizeof(":irc.local 001 suhkim :Welcome to the Localnet IRC Network suhkim!root@127.0.0.1"), 0);
					}
					else if (strstr(buf, "MODE"))
					{
						send(clntSock, ":suhkim!root@127.0.0.1 MODE <input nick name> :+i\n", \
								sizeof(":suhkim!root@127.0.0.1 MODE <input nick name> :+i"), 0);
					}
					else if (strstr(buf, "PING"))
					{
						send(clntSock, ":irc.local PONG irc.local :irc.local\n", \
								sizeof(":irc.local PONG irc.local :irc.local"), 0);
					}
					memset(buf, 0, BUF_SIZE);
				}
			}
		}
	}
	close(_servSock);
	close(epfd);
}

void	addChannel(std::string name)
{
	_channelList.pushback(Channel(name));
}

void	addClient(int sock)
{
	_clntList.pushback(Client(sock));
}

int	Server::getPort() const
{
	return (_port);
}

const std::string&	Server::getPass() const
{
	return (_passWord);
}


