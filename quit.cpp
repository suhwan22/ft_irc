#include "cmd.hpp"
#include "client.hpp"

void	cmd::quit(string arg)
{
	Client	*me = searchClient(_clntSock);
	string	msg;

	me->cleanChannel();
	/* quit 를 하는 client 한테 보내는 메세지 */
	msg = "ERROR :Closing link: (" + me->getUserName() + "@127.0.0.1) [Quit: " + arg + "]\r\n";
	if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
		cout << "quit send fail?" << endl;

	/* client 가 quit 한다고 다른 client한테 보내는 메세지 */
	msg = ":" + me->getNickname() + "!" + me->getUserName() + "@127.0.0.1 QUIT :Quit: " + arg + "\r\n";
	for (vector<Client *>::iterator it = _clntList.begin(); it != _clntList.end(); it++)
		if ((*it) != me)
			send((*it)->getSock(), msg.c_str(), msg.size(), 0);
}
