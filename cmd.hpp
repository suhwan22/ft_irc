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
	vector<string> _command;
	vector<Client *>& _clilist;
	vector<Channel *>& _chlist;

 public:
	cmd(char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist);
	~cmd();
	std::vector<string> *splitCmd(string &str);
	void printCmdVector(const vector<string>& cmdVector);
	int parsecommand();

	void privmsg(vector<string> tokens);
	void privmsgToChannel(vector<string> tokens);
	void privmsgToClient(vector<string> tokens);

	const vector<string>& getCommand() const;
};

#endif
