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
	if (argc != 2)
	{
		std::cout << "Usage: " << argv[0] << " <port>" << std::endl;
		exit(1);
	}
	Server _server(atoi(argv[1]), "1234");
	_server.serverInit();
	_server.serverStart();
	close(_server.getSock());
	//close(epfd);
	return (0);
}
