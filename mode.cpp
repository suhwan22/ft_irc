#include "cmd.hpp"
#include "client.hpp"
#include "channel.hpp"

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
	else if ()

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

void cmd::plusOption_k(string channel, string pass)
{
	string msg;
	vector<Channel *>::iterator iter;
	Client	*me = searchClient(_clntSock);
	for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
		if ((*iter)->getChannelName() == channel) {
			vector<Client *> members = (*iter)->getUsers();
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + channel + " :You must have channel op access or above to set channel mode k\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				if ((*iter)->getChPassFlag() == true)
					return ;
				else {
					_chpass = pass;
					for (int i = 0; i < (int)members.size(); i++) {
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + channel + " +k :" + pass + "/r/n";
						if (send(members[i]->getSock(), msg.c_str(), msg.size(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
					(*iter)->setChPassFlag(true);
				}
			}
		}
	}
}

void cmd::minusOption_k(string channel, string pass)
{
	string msg;
	vector<Channel *>::iterator iter;
	Client	*me = searchClient(_clntSock);
	for (iter = _chlist.begin(); iter != _chlist.end(); iter++) {
		if ((*iter)->getChannelName() == channel) {
			vector<Client *> members = (*iter)->getUsers();
			if (!(*iter)->isClientOp(me)) {
				msg = ":irc.local 482 " + me->getNickname() + " " + channel + " :You must have channel op access or above to set channel mode k\r\n";
				if (send(_clntSock, msg.c_str(), msg.size(), 0) == -1)
					cerr << "Error: send error" << endl;
				return ;
			}
			else {
				if ((*iter)->getChPassFlag() == false)
					return ;
				else {
					_chpass = "";
					for (int i = 0; i < (int)members.size(); i++){
						msg = ":" + me->getNickname() + "!" + me->getUserName() + "@" + me->getIP() + " MODE " + channel + " -k :" + pass + "/r/n";
						if (send(members[i]->getSock(), msg.c_str(), msg.length(), 0) == -1)
							cerr << "Error: send error" << endl;
					}
					(*iter)->setChPassFlag(false);
				}
			}
		}
	}
}



void cmd::modeToChannel(string arg, string line)
{
	string line_two;
	stringstream tmp;
	tmp = stringstream(line);
	tmp >> line;
	getline(tmp, line_two, static_cast<char>(EOF));
	line_two.erase(0, 1);
	if (line[1] == 'k')
		mode_k(arg, line, line_two);
}

void cmd::modeToClient(string line)
{
	string			line_two;
	stringstream	tmp;
	string			msg;
	Client			*me = searchClient(_clntSock);
	tmp = stringstream(line);
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
	stringstream tmp;
	tmp = stringstream(arg);
	tmp >> arg;
	line.erase(0, 1);
	getline(tmp, line, static_cast<char>(EOF));
	if (arg[0] == '#')
		modeToChannel(arg, line);
	
	else
		modeToClient(line);
}