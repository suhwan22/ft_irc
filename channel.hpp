#ifndef CHANNEL_HPP
# define CHANNEL_HPP

# include <iostream>
# include <string>
# include <vector>

class Client;

class Channel
{
	private:
		std::string				_channelName;
		std::string				_passWord;
		std::vector<Client *>	_users;
		std::vector<Client *>	_opUsers;
		std::string				_topic;
		int						_userLimit;
		bool					_kflag;
		bool					_iflag;
		bool					_tflag;
		bool					_lflag;

		/* option flag */
		bool					_kflag;
		bool					_iflag;
		bool					_tflag;
		bool					_lflag;

	public:
		Channel(std::string channelName);
		Channel(std::string channelName, std::string password);
		~Channel();

		void	addUser(Client *client);
		void	delUser(Client *client);

		void	addOpUser(Client *client);
		void	delOpUser(Client *client);

		bool	isClientOp(Client *client);
		bool	isClientInChannel(Client *client);

		/* setter func */
		void	setPassWord(const std::string passWord);
		void	setUserLimit(const int limit);
		void	setTopic(const std::string topic);

		void	setInviteOnlyFlag(const bool flag);
		void	setChPassFlag(const bool flag);
		void	setChTopicFlag(const bool flag);
		void	setChLimitFlag(const bool flag);

		/* getter func */
		std::string						getUsersName();
		const std::vector<Client *>&	getUsers() const;
		const std::string&				getChannelName() const;
		const std::string&				getPassWord() const;
		int								getUserLimit() const;
		bool							getInviteOnlyFlag() const;
		bool							getChPassFlag() const;
		bool							getChTopicFlag() const;
		bool							getChLimitFlag() const;
};

#endif