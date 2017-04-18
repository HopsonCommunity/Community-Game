#pragma once

#include <exception>
#include <iostream>

namespace Exceptions
{
	class ExceptionBase : public std::exception
	{
	public:
		ExceptionBase(const std::string& text);
		const char* what() const throw();
	protected:
		std::string m_msg;
	};

	class CannotGetResource : public ExceptionBase
	{
	public:
		CannotGetResource(const std::string& full);
	};
};
