#include <exception>
#include "LuaType.hpp"
#include <string>

namespace saturn
{
	class LuaException : public std::exception
	{
	protected:
		std::string msg;

	public:
		LuaException(const std::string& msg = "");

		const char* what();
	};

	class LuaInvalidType : public LuaException
	{
	public:
		LuaInvalidType(LuaType expected);
		LuaInvalidType(LuaType expected, LuaType actual);
	};

	class LuaCallError : public LuaException
	{
	public:
		LuaCallError(const std::string& msg);
	};

	class LuaLoadError : public LuaException
	{
	public:
		LuaLoadError(const std::string& msg);
	};
}