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
	vector<Client *>&	_clntList;
	vector<Channel *>&	_chList;
	string				_servPass;
	string				_chpass;
	bool				_kflag;

 public:
	cmd(int clntSock, char *buf, int strlen, string servpass, vector<Client *> &clntList, vector<Channel *> &chList);
	~cmd();
	std::vector<string> *splitCmd(string &str);
	void	printContent(const vector<content>& content);
	int		parsecommand();

	Channel	*addChannel(std::string name);
	void	delChannel(Channel *channel);
	Channel	*searchChannel(string channelName);

	Client	*addClient(int sock);
	void	delClient(Client *client);
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

	/* quit.cpp */
	void	quit(string arg);

	/* join.cpp */
	void	join(string arg);
	void	joinWithPass(vector<string> &chList, vector<string> &passList);
	void	joinNoPass(vector<string> &chList);
	void	joinNewChannel(Client *me, string channel);
	void	joinExistChannel(Client *me, Channel *ch, string pass);

	/* util.cpp */
	void noSuchNick(string wrongnick);
	void noSuchChannel(string wrongchannel);
	bool hasSpecialCharacter(const std::string& str);

	/* privmsg.cpp */
	void privmsg(string arg);
	void privmsgToClient(string arg, string inputmsg);
	void privmsgToChannel(string arg, string inputmsg);

	/* topic.cpp */
	void topic(string arg);
	void settingtopic(string arg, string inputmsg);

	/* mode.cpp */
	void mode(string arg);
	void modeToChannel(string arg, string line);
	void modeToClient(string line);
	void mode_k(string channel, string option, string pass);
	void plusOption_k(string channel, string option, string pass);
	void minusOption_k(string channel, string option, string pass);

	const	vector<content>& getContent() const;
};

#endif
