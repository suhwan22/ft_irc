#include "cmd.hpp"
#include "client.hpp"

void	cmd::pass(string pass)
{
	searchClient(_clntSock)->setPass(pass);
}
