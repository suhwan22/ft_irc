#ifndef CMD_HPP
# define CMD_HPP

#include "client.hpp"
#include "server.hpp"
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>

using namespace std;

class cmd {
 private:
	int					_clntSock;
	vector<string>		_command;
	vector<string>		_arg;
	vector<Client *>&	_clilist;
	vector<Channel *>&	_chlist;

 public:
	cmd(int clntSock, char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist);
	~cmd();
	std::vector<string> *splitCmd(string &str);
	void	printCmdVector(const vector<string>& cmdVector, const vector<string>& argVector);
	int		parsecommand();
	Client	*searchClient(int sock);

	/* privmsg.cpp */
	void	privmsg(vector<string> tokens);
	void	privmsgToChannel(vector<string> tokens);
	void	privmsgToClient(vector<string> tokens);

	/* user.cpp */
	//void	user(

	/* nick.cpp */

	/* pass.cpp */

	const vector<string> getCommand() const;
	const vector<string> getArgument() const;
};

#endif
