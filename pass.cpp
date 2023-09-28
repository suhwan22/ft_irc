#include "cmd.hpp"
#include "client.hpp"

void	cmd::pass(string pass)
{
	pass.erase(pass.size() -1, 1);
	searchClient(_clntSock)->setPass(pass);
}
