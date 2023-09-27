#ifndef CMD_HPP
# define CMD_HPP

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <sstream>
#include <unistd.h>
#include <arpa/inet.h>

using namespace std;

class Client;
class Channel;

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
	string				_servPass;

 public:
	cmd(int clntSock, char *buf, int strlen, string servpass, vector<Client *> &clilist, vector<Channel *> &chlist);
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

	/* ping.cpp */
	void ping(string arg);
	const	vector<content>& getContent() const;
};

#endif
