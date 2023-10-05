#ifndef CONTENT_HPP
# define CONTENT_HPP

# include "server.hpp"

/* _cmd : CMD without "\r\n", _arg : ARG withoug \r\n */

class Content
{
	private:
		std::string	_cmd;
		std::string	_arg;

		Content();
	public:
		Content(std::string cmd, std::string arg);
		~Content();
};

#endif
