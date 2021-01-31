#include <exception>
#include "LuaType.hpp"
#include <string>

class InvalidLuaType : public std::exception
{
private:
	std::string msg;

public:
	InvalidLuaType(LuaType expected);
	InvalidLuaType(LuaType expected, LuaType actual);

	const char* what();
};