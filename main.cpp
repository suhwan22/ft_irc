#include <iostream>
#include <cstdlib>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <string>
#include <vector>
#define BUF_SIZE 100
#define EPOLL_SIZE 50

#include "server.hpp"
#include "client.hpp"


void printCmdVector(const std::vector<std::string>& cmdVector) {
    for (auto it = cmdVector.begin(); it != cmdVector.end(); ++it) {
        std::cout << *it << std::endl;
    }
}

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		std::cout << "Usage: " << v[0] << " <port> <pass>" << std::endl;
		exit(1);
	}
	Server _server(atoi(argv[1]), argv[2]);
	_server.serverInit();
	_server.serverStart();
	//close(_server.getSock());
	//close(epfd);
	return (0);
}
