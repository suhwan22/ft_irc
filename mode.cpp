#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

void cmd::mode_i(string ch_name, string option) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	if (option[0] == '+') {
		for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)){
					sendNotOpMsg(ch_name, "i", false);
					return ;
				}
				else {
					if (!(*iter)->getInviteOnlyFlag() == true)
						return ;
					else {
						for (int i = 0; (int)members.size(); i++) {
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :+i\r\n";
							if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setInviteOnlyFlag(true);
				}
			}
		}
		noSuchChannel(ch_name);
	}
	else if (option[0] == '-') {
		for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)){
					sendNotOpMsg(ch_name, "i", false);
					return ;
				}
				else {
					if (!(*iter)->getInviteOnlyFlag() == false)
						return ;
					else {
						for (int i = 0; (int)members.size(); i++) {
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :-i\r\n";
							if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setInviteOnlyFlag(false);
				}
			}
		}
		noSuchChannel(ch_name);
	}
}

void cmd::mode_t(string ch_name, string option) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	if (option[0] == '+') {
		for (iter = _chlist.begin(); iter != _chlist.end(); iter++){
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)) {
					sendNotOpMsg(ch_name, "t", false);
					return ;
				}
				else {
					if ((*iter)->getChTopicFlag() == true)
						return ;
					else {
						for (int i = 0; (int)members.size(); i++){
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :+t\r\n";
							if(send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChTopicFlag(true);
				}
			}
		}
		noSuchChannel(ch_name);
	}
	else if (option[0] == '-') {
		for (iter = _chlist.begin(); iter != _chlist.end(); iter++){
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)) {
					sendNotOpMsg(ch_name, "t", true);
					return ;
				}
				else {
					if ((*iter)->getChTopicFlag() == false)
						return ;
					else {
						for (int i = 0; (int)members.size(); i++){
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :-t\r\n";
							if(send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChTopicFlag(false);
				}
			}
		}
		noSuchChannel(ch_name);
	}
}


void cmd::mode_o(string channel, string option, string nick) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	if (nick.empty()){
		msg = ":irc.local 696 " + me->getNickname() + " " + channel + " k * :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	if (option[0] == '+')
		plusOption_o(channel, nick);
	else if (option[0] == '-')
		minusOption_o(channel, nick);
}

void cmd::minusOption_o(string ch_name, string nick)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	for (iter = _chlist.begin(); iter != _chlist.end(); iter++)
	{
		if ((*iter)->getChannelName() == ch_name){
			vector<Client *> members = (*iter)->getUsers();
			vector<Client *>::iterator cliter;
			if (!(*iter)->isClientOp(me)) {
				sendNotOpMsg(ch_name, "o", true);
				return ;
			}
			else {
				for (cliter = _clilist.begin(); cliter != _clilist.end(); cliter++){
					if ((*cliter)->getNickname() == nick){
						if (!(*iter)->isClientOp(*cliter))
							return ;
						else {
							(*iter)->delOpUser(*cliter);
							for (int i = 0; (int)i < members.size(); i++) {
								msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + "-o :" + nick + "\r\n";
								if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
									cerr << "Error: send error" << endl;
							}
						}
					}
				}
				noSuchNick(nick);
			}
		}
		return ;
	}
	noSuchChannel(ch_name);
}


void cmd::plusOption_o(string ch_name, string nick)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	for (iter = _chlist.begin(); iter != _chlist.end(); iter++)
	{
		if ((*iter)->getChannelName() == ch_name){
			vector<Client *> members = (*iter)->getUsers();
			vector<Client *>::iterator cliter;
			if (!(*iter)->isClientOp(me)) {
				sendNotOpMsg(ch_name, "o", false);
				return ;
			}
			else {
				for (cliter = _clilist.begin(); cliter != _clilist.end(); cliter++){
					if ((*cliter)->getNickname() == nick){
						if ((*iter)->isClientOp(*cliter))
							return ;
						else {
							(*iter)->addOpUser(*cliter);
							for (int i = 0; (int)i < members.size(); i++) {
								msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + "+o :" + nick + "\r\n";
								if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
									cerr << "Error: send error" << endl;
							}
						}
					}
				}
				noSuchNick(nick);
			}
		}
		return ;
	}
	noSuchChannel(ch_name);
}

void cmd::mode_l(string channel, string option, string num) {
	string msg;
	Client *me = searchClient(_clntSock);
	if (num.empty()){
		msg = ":irc.local 696 " + me->getNickname() + " " + channel + " l * :You must specify a parameter for the limit mode. Syntax: <limit>.\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	else if (strtod(num.c_str(), NULL) < 0)
	{
		msg = ":irc.local 696 " + me->getNickname() + " " + channel + " l " + num + " :Invalid limit mode parameter. Syntax: <limit>.\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	if (option[0] == '+')
		plusOption_l(channel, num);
	else if(option[0] == '-')
		minusOption_l(channel, num);
}

void cmd::plusOption_l(string ch_name, string num)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;
	int							limitnum;

	limitnum = strtod(num.c_str(), NULL);
	for (iter = _chlist.begin(); iter != _chlist.end(); iter++)
	{
		vector<Client *> members = (*iter)->getUsers();
		if ((*iter)->getChannelName() == ch_name){
			if(!(*iter)->isClientOp(me)) {
				sendNotOpMsg(ch_name, "l", false);
				return ;
			}
			else {
				if ((*iter)->getUserLimit() == limitnum)
					return ;
				else {
					(*iter)->setUserLimit(limitnum);
					for (int i = 0; (int)i < members.size(); i++) {
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " +l :" + num + "\r\n";
						if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
				}
				(*iter)->setChLimitFlag(true);
			}
			return ;
		}
	}
	noSuchChannel(ch_name);
}

void cmd::minusOption_l(string ch_name, string num)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;
	for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
		vector<Client *> members = (*iter)->getUsers();
		if ((*iter)->getChannelName() == ch_name){
			if (!(*iter)->isClientOp(me)) {
				sendNotOpMsg(ch_name, "l", true);
				return ;
				}
			else {
				if ((*iter)->getChLimitFlag() == false)
					return ;
				else {
					(*iter)->setUserLimit(2147483647);
					for (int i = 0; (int)i < members.size(); i++) {
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :-l\r\n";
						if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChLimitFlag(false);
			}
			return ;
		}
	}
	noSuchChannel(ch_name);
}

void cmd::mode_k(string channel, string option, string pass) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	if (pass.empty()){
		msg = ":irc.local 696 " + me->getNickname() + " " + channel + " k * :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	if (option[0] == '+')
		plusOption_k(channel, pass);
	else if (option[0] == '-')
		minusOption_k(channel, pass);
}

void cmd::plusOption_k(string ch_name, string pass)
{
	string msg;
	vector<Channel *>::iterator iter;
	Client	*me = searchClient(_clntSock);

	for (iter = _chList.begin(); iter != _chList.end(); iter++) {
		if ((*iter)->getChannelName() == channel) {
			vector<Client *> members = (*iter)->getUsers();
			if (!(*iter)->isClientOp(me)) {
				sendNotOpMsg(ch_name, "k", false);
				return ;
			}
			else {
				if ((*iter)->getChPassFlag() == true)
					return ;
				else {
					_chpass = pass;
					for (int i = 0; i < (int)members.size(); i++) {
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " +k :" + pass + "/r/n";
						if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
				}
				(*iter)->setChPassFlag(true);
			}
			return ;
		}
	}
	noSuchChannel(ch_name);
}

void cmd::minusOption_k(string ch_name, string pass)
{
	string msg;
	vector<Channel *>::iterator iter;
	Client	*me = searchClient(_clntSock);

	for (iter = _chList.begin(); iter != _chList.end(); iter++) {
		if ((*iter)->getChannelName() == channel) {
			vector<Client *> members = (*iter)->getUsers();
			if (!(*iter)->isClientOp(me)) {
				sendNotOpMsg(ch_name, "k", true);
				return ;
			}
			else {
				if ((*iter)->getChPassFlag() == false)
					return ;
				else {
					_chpass = "";
					for (int i = 0; i < (int)members.size(); i++){
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " -k :" + pass + "/r/n";
						if (send(members[i]->getSock(), msg.c_str(), msg.length(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
				}
				(*iter)->setChPassFlag(false);
			}
			return ;
		}
	}
	noSuchChannel(ch_name);
}

void cmd::onlyChannel(string ch_name)
{
	string	msg;
	Client	*me = searchClient(_clntSock);

	msg = ":irc.local 324 " + me->getNickname() + " " + ch_name + " :+nt\r\n" + \
		":irc.local 329 " + me->getNickname() + " " + ch_name + " \r\n"; //채널고유번호가 들어가는곳
	if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
		cerr << "Error: send error" << endl;
}

void cmd::chModeB(string ch_name)
{
	string	msg;
	Client	*me = searchClient(_clntSock);

	msg = ":irc.local 368 " + me->getNickname() + " " + ch_name + " :End of channel ban list\r\n";
	if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
		cerr << "Error: send error" << endl;
}

void cmd::modeToChannel(string arg, string line)
{
	string line_two;
	stringstream tmp(line);
	tmp >> line;
	getline(tmp, line_two, static_cast<char>(EOF));
	line_two.erase(0, 1);
	if (line[1] == 'k')
		mode_k(arg, line, line_two);
	else if (line[1] == 'l')
		mode_l(arg, line, line_two);
	else if (line[1] == 'i')
		mode_i(arg, line);
	else if (line[1] == 't')
		mode_t(arg, line);
	else if (line[1] == 'o')
		mode_o(arg, line, line_two);
	else if (line.empty())
		onlyChannel(arg);
	else if (line[0] == 'b')
		chModeB(arg);
	
}

void cmd::modeToClient(string line)
{
	string			line_two;
	stringstream	tmp(line);
	string			msg;
	Client			*me = searchClient(_clntSock);
	tmp >> line;
	getline(tmp, line_two, static_cast<char>(EOF));
	line_two.erase(0, 1);
	if (line[1] == 'i')
	{
		msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + me->getNickname() + " :+i\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
	}
	else {
		msg = "Error: parameters error\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
	}
}

void cmd::mode(string arg)
{
	string msg;
	string line;
	stringstream tmp(arg);
	tmp >> arg;
	line.erase(0, 1);
	getline(tmp, line, static_cast<char>(EOF));
	if (arg[0] == '#')
		modeToChannel(arg, line);
	
	else
		modeToClient(line);
}
