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

struct content
{
	string	cmd;
	string	arg;
};

class cmd {
 private:
	int					_clntSock;
	vector<content>		_content;
	vector<Client *>&	_clilist;
	vector<Channel *>&	_chlist;

 public:
	cmd(int clntSock, char *buf, int strlen, vector<Client *> &clilist, vector<Channel *> &chlist);
	~cmd();
	std::vector<string> *splitCmd(string &str);
	void	printContent(const vector<content>& content);
	int		parsecommand();
	Client	*searchClient(int sock);

	/* privmsg.cpp */
	void	privmsg(string arg);
	void	privmsgToChannel(string arg, string inputmsg);
	void	privmsgToClient(string arg, string inputmsg);

	/* user.cpp */
	//void	user(

	/* nick.cpp */

	/* pass.cpp */

	/* util.cpp */
	void noSuchNick(string wrongnick);
	void noSuchChannel(string wrongchannel);
	bool isFirstCharacterHash(const std::string& str);
	const	vector<content>& getContent() const;
};

#endif
