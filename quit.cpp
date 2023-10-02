#include "cmd.hpp"
#include "client.hpp"

void	cmd::quit(string arg)
{
	Client	*client = searchClient(_clntSock);
	string	msg;

	msg = "ERROR :Closing link: (" + client->getUserName() + "@127.0.0.1) [Quit: " + arg + "]\r\n";

	if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
		cout << "quit send fail?" << endl;
}
