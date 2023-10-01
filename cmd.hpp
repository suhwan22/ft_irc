#ifndef CMD_HPP
# define CMD_HPP

# include <iostream>
# include <vector>
# include <cstring>
# include <cstdio>
# include <string>
# include <sstream>
# include <arpa/inet.h>

using namespace std;

class Channel;
class Client;

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
	string				_chpass;
	int					_kflag;

 public:
	cmd(int clntSock, char *buf, int strlen, string servpass, vector<Client *> &clilist, vector<Channel *> &chlist);
	~cmd();
	std::vector<string> *splitCmd(string &str);
	void	printContent(const vector<content>& content);
	int		parsecommand();
	Client	*searchClient(int sock);

	/* privmsg.cpp */
	void	privmsg(vector<string> tokens);
	void	privmsgToChannel(vector<string> tokens);
	void	privmsgToClient(vector<string> tokens);

	/* user.cpp */
	void	user(string arg);

	/* nick.cpp */
	void	nick(string nick);

	/* pass.cpp */
	void	pass(string pass);

	/* ping.cpp */
	void	ping();

	/* util.cpp */
	void noSuchNick(string wrongnick);
	void noSuchChannel(string wrongchannel);
	bool hasSpecialCharacter(const std::string& str);
	void sendNotOpMsg(string channel, string mode, bool flag);

	/* privmsg.cpp */
	void privmsg(string arg);
	void privmsgToClient(string arg, string inputmsg);
	void privmsgToChannel(string arg, string inputmsg);

	/* topic.cpp */
	void topic(string arg);
	void settingtopic(string arg, string inputmsg);

	/* mode.cpp */
	void mode(string arg);
	void onlyChannel(string ch_name);
	void chModeB(string ch_name);
	void modeToChannel(string arg, string line);
	void modeToClient(string line);
	void mode_k(string channel, string option, string pass);
	void plusOption_k(string ch_name, string pass);
	void minusOption_k(string ch_name, string pass);
	void mode_l(string channel, string option, string num);
	void plusOption_l(string ch_name, string num);
	void minusOption_l(string ch_name, string num);
	void mode_o(string channel, string option, string nick);
	void plusOption_o(string ch_name, string nick);
	void minusOption_o(string ch_name, string nick);
	void mode_t(string ch_name, string option);

	const	vector<content>& getContent() const;
};

#endif
