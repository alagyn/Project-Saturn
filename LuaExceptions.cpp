#include "LuaExceptions.hpp"
#include "LuaType.hpp"
#include <sstream>

using namespace std;

LuaException::LuaException(const string& msg) :
	msg(msg)
{

}

const char* LuaException::what()
{
	return msg.c_str();
}

LuaInvalidType::LuaInvalidType(LuaType expected)
{
	stringstream x;
	x << "Invalid Lua type, expected: ";
	x << getTypeString(expected);

	msg = x.str();
}

LuaInvalidType::LuaInvalidType(LuaType expected, LuaType actual)
{
	stringstream x;
	x << "Invalid Lua type, expected: ";
	x << getTypeString(expected);
	x << ", got: " << getTypeString(actual);

	msg = x.str();
}

LuaCallError::LuaCallError(const std::string& msg)
{
	stringstream x;
	x << "Lua Call Error: " << msg;
	this->msg = x.str();
}

LuaLoadError::LuaLoadError(const std::string& msg)
{
	stringstream x;
	x << "Lua Load Error: " << msg;
	this->msg = x.str();
}

