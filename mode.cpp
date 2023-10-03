#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"
#include <cstdlib>

void cmd::mode_i(string ch_name, char option) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	if (option == '+') {
		for (iter = _chList.begin(); iter != _chList.end(); iter++) {
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)){
					msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
						" :You must have channel op access or above to set channel mode i\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					return ;
				}
				else {
					if ((*iter)->getInviteOnlyFlag() == true)
						return ;
					else {
						for (int i = 0; i < (int)members.size(); i++) {
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :+i\r\n";
							if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setInviteOnlyFlag(true);
					return ;
				}
			}
		}
		noSuchChannel(ch_name);
	}
	else if (option == '-') {
		for (iter = _chList.begin(); iter != _chList.end(); iter++) {
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)){
					msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
						" :You must have channel op access or above to unset channel mode i\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					return ;
				}
				else {
					if ((*iter)->getInviteOnlyFlag() == false)
						return ;
					else {
						for (int i = 0; i < (int)members.size(); i++) {
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :-i\r\n";
							if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setInviteOnlyFlag(false);
					return ;
				}
			}
		}
		noSuchChannel(ch_name);
	}
}

void cmd::mode_t(string ch_name, char option) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	if (option == '+') {
		for (iter = _chList.begin(); iter != _chList.end(); iter++){
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)) {
					msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
						" :You must have channel op access or above to set channel mode t\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					return ;
				}
				else {
					if ((*iter)->getChTopicFlag() == true)
						return ;
					else {
						for (int i = 0; i < (int)members.size(); i++){
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :+t\r\n";
							if(send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChTopicFlag(true);
					return ;
				}
			}
		}
		noSuchChannel(ch_name);
	}
	else if (option == '-') {
		for (iter = _chList.begin(); iter != _chList.end(); iter++){
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)) {
					msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
						" :You must have channel op access or above to unset channel mode t\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					return ;
				}
				else {
					if ((*iter)->getChTopicFlag() == false)
						return ;
					else {
						for (int i = 0; i < (int)members.size(); i++){
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :-t\r\n";
							if(send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChTopicFlag(false);
					return ;
				}
			}
		}
		noSuchChannel(ch_name);
	}
}


void cmd::mode_o(string channel, char option, string nick) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	if (nick.empty()){
		msg = ":irc.local 696 " + me->getNickname() + " " + channel + " k * :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	if (option == '+')
		plusOption_o(channel, nick);
	else if (option == '-')
		minusOption_o(channel, nick);
}

void cmd::minusOption_o(string ch_name, string nick)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	for (iter = _chList.begin(); iter != _chList.end(); iter++)
	{
		if ((*iter)->getChannelName() == ch_name){
			vector<Client *> members = (*iter)->getUsers();
			vector<Client *>::iterator cliter;
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
					" :You must have channel op access or above to unset channel mode o\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				for (cliter = _clntList.begin(); cliter != _clntList.end(); cliter++){
					if ((*cliter)->getNickname() == nick){
						if (!(*iter)->isClientOp(*cliter) || !(*iter)->isClientInChannel(*cliter))
							return ;
						else {
							(*iter)->delOpUser(*cliter);
							for (int i = 0; i < (int)members.size(); i++) {
								msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " -o :" + nick + "\r\n";
								if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
									cerr << "Error: send error" << endl;
							}
						}
						return ;
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

	for (iter = _chList.begin(); iter != _chList.end(); iter++)
	{
		if ((*iter)->getChannelName() == ch_name){
			vector<Client *> members = (*iter)->getUsers();
			vector<Client *>::iterator cliter;
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
					" :You must have channel op access or above to set channel mode o\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				for (cliter = _clntList.begin(); cliter != _clntList.end(); cliter++){
					if ((*cliter)->getNickname() == nick){
						if ((*iter)->isClientOp(*cliter) || !(*iter)->isClientInChannel(*cliter))
							return ;
						else {
							for (int i = 0; i < (int)members.size(); i++) {
								msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " +o :" + nick + "\r\n";
								if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
									cerr << "Error: send error" << endl;
							}
							(*iter)->addOpUser(*cliter);
						}
						return ;
					}
				}
				noSuchNick(nick);
			}
		}
		return ;
	}
	noSuchChannel(ch_name);
}

void cmd::mode_n(string ch_name, char option)
{
	string	msg;
	Client	*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;

	if (option == '+') {
		for (iter = _chList.begin(); iter != _chList.end(); iter++){
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)) {
					msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
						" :You must have channel op access or above to set channel mode t\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					return ;
				}
				else {
					if ((*iter)->getChNFlag() == true)
						return ;
					else {
						for (int i = 0; i < (int)members.size(); i++){
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :+n\r\n";
							if(send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChNFlag(true);
					return ;
				}
			}
		}
		noSuchChannel(ch_name);
	}
	else if (option == '-') {
		for (iter = _chList.begin(); iter != _chList.end(); iter++){
			if ((*iter)->getChannelName() == ch_name) {
				vector<Client *> members = (*iter)->getUsers();
				if (!(*iter)->isClientOp(me)) {
					msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
						" :You must have channel op access or above to unset channel mode t\r\n";
					if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
						cerr << "Error: send error" << endl;
					return ;
				}
				else {
					if ((*iter)->getChNFlag() == false)
						return ;
					else {
						for (int i = 0; i < (int)members.size(); i++){
							msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " :-n\r\n";
							if(send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
								cerr << "Error: send error" << endl;
						}
					}
					(*iter)->setChNFlag(false);
					return ;
				}
			}
		}
		noSuchChannel(ch_name);
	}
}

void cmd::mode_l(string channel, char option, string num) {
	string msg;
	Client *me = searchClient(_clntSock);
	if (num.empty() && option == '+'){
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
	if (option == '+')
		plusOption_l(channel, num);
	else if(option == '-')
		minusOption_l(channel);
}

void cmd::plusOption_l(string ch_name, string num)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;
	int							limitnum;

	limitnum = strtod(num.c_str(), NULL);
	if (limitnum == 0)
		num = "0";
	for (iter = _chList.begin(); iter != _chList.end(); iter++)
	{
		vector<Client *> members = (*iter)->getUsers();
		if ((*iter)->getChannelName() == ch_name){
			if(!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
					" :You must have channel op access or above to set channel mode l\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				if ((*iter)->getUserLimit() == limitnum)
					return ;
				else {
					(*iter)->setUserLimit(limitnum);
					for (int i = 0; i < (int)members.size(); i++) {
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

void cmd::minusOption_l(string ch_name)
{
	string						msg;
	Client						*me = searchClient(_clntSock);
	vector<Channel *>::iterator iter;
	for (iter = _chList.begin(); iter != _chList.end(); iter++) {
		vector<Client *> members = (*iter)->getUsers();
		if ((*iter)->getChannelName() == ch_name){
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
					" :You must have channel op access or above to unset channel mode l\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
				}
			else {
				if ((*iter)->getChLimitFlag() == false)
					return ;
				else {
					(*iter)->setUserLimit(2147483647);
					for (int i = 0; i < (int)members.size(); i++) {
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

void cmd::mode_k(string channel, char option, string pass) {
	string	msg;
	Client	*me = searchClient(_clntSock);
	if (pass.empty()){
		msg = ":irc.local 696 " + me->getNickname() + " " + channel + " k * :You must specify a parameter for the key mode. Syntax: <key>.\r\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	if (option == '+')
		plusOption_k(channel, pass);
	else if (option == '-')
		minusOption_k(channel, pass);
}

void cmd::plusOption_k(string ch_name, string pass)
{
	string msg;
	vector<Channel *>::iterator iter;
	Client	*me = searchClient(_clntSock);

	for (iter = _chList.begin(); iter != _chList.end(); iter++) {
		if ((*iter)->getChannelName() == ch_name) {
			vector<Client *> members = (*iter)->getUsers();
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
					" :You must have channel op access or above to set channel mode k\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				if ((*iter)->getChPassFlag() == true)
					return ;
				else {
					for (int i = 0; i < (int)members.size(); i++) {
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " +k :" + pass + "\r\n";
						if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
				}
				(*iter)->setPassWord(pass);
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
		if ((*iter)->getChannelName() == ch_name) {
			vector<Client *> members = (*iter)->getUsers();
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + ch_name + \
					" :You must have channel op access or above to unset channel mode k\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				if ((*iter)->getChPassFlag() == false)
					return ;
				else {
					for (int i = 0; i < (int)members.size(); i++){
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + ch_name + " -k :" + pass + "\r\n";
						if (send(members[i]->getSock(), msg.c_str(), msg.length(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
				}
				(*iter)->setPassWord("");
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
	Channel	*ch = searchChannel(ch_name);
	string	opt = ch->getOption(me);

	msg = ":irc.local 324 " + me->getNickname() + " " + ch_name + " " + opt + "\r\n" + \
		":irc.local 329 " + me->getNickname() + " " + ch_name + " :" + ch->getChannelTime() + "\r\n";
	if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
		cerr << "Error: send error" << endl;
}

void cmd::mode_b(string ch_name, char option)
{
	string	msg;
	Client	*me = searchClient(_clntSock);

	if (option == '-')
		return ;
	msg = ":irc.local 368 " + me->getNickname() + " " + ch_name + " :End of channel ban list\r\n";
	if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
		cerr << "Error: send error" << endl;
}

void	cmd::error_arg(char c)
{
	string	tmp;
	Client	*me = searchClient(_clntSock);

	tmp.push_back(c);

	string	msg = ":irc.local 472 " + me->getNickname() + " " + tmp + " :is not a recognised channel mode.\r\n";
	send(_clntSock, msg.c_str(), msg.size(), 0);
}

void cmd::modeToChannel(string chName, string line)
{
	stringstream	tmp(line);
	string	msg;
	string	opt;
	vector<string>	args;
	string			arg;

	if (line.empty())
	{
		onlyChannel(chName);
		return ;
	}

	tmp >> opt;
	while (!tmp.eof())
	{
		tmp >> line;
		args.insert(args.begin(), line);
	}

	if (opt[0] == 'b')
	{
		mode_b(chName, '+');
		return ;
	}

	size_t	idx = 1;
	for (;idx < opt.size(); idx++)
	{
		if (args.empty())
			arg = "";
		else
			arg = args.back();
		if (opt[idx] == 'k' || opt[idx] == 'l' || opt[idx] == 'o')
		{
			if (opt[idx] == 'k')
			{
				mode_k(chName, opt[0], arg);
				if (!args.empty())
					args.pop_back();
			}
			else if (opt[idx] == 'l')
			{
				mode_l(chName, opt[0], arg);
				if (opt[0] == '+')
					if (!args.empty())
						args.pop_back();
			}
			else if (opt[idx] == 'o')
			{
				mode_o(chName, opt[0], arg);
				if (!args.empty())
					args.pop_back();
			}
		}
		else
		{
			if (opt[idx] == 'i')
				mode_i(chName, opt[0]);
			else if (opt[idx] == 't')
				mode_t(chName, opt[0]);
			else if (opt[idx] == 'n')
				mode_n(chName, opt[0]);
			else if (opt[idx] == 'b')
				mode_b(chName, opt[0]);
			else
				error_arg(opt[idx]);
		}
	}	
}

void cmd::modeToClient(string clntName, string opt)
{
	string			msg;
	string			sign;
	Client			*me = searchClient(_clntSock);

	if (me->getNickname() != clntName)
	{
		msg = ":irc.local 502 " + me->getNickname() + " :Can't change mode for other users\r\n";
		send(_clntSock, msg.c_str(), msg.size(), 0);
		return ;
	}
	if (opt.size() != 2)
	{
		msg = "Error: parameters error\n";
		if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
			cerr << "Error: send error" << endl;
		return ;
	}
	if (opt[1] == 'i')
	{
		if (opt[0] == '-')
			sign = "-";
		else
			sign = "+";

		msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + me->getNickname() + " :" + sign + "i\r\n";
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
	string line;
	stringstream tmp(arg);

	tmp >> arg;
	getline(tmp, line, static_cast<char>(EOF));
	line.erase(0, 1);

	if (arg[0] == '#')
		modeToChannel(arg, line);
	else
		modeToClient(arg, line);
}
