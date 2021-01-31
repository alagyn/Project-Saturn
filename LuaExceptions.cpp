#include "LuaExceptions.hpp"
#include "LuaType.hpp"
#include <sstream>

using namespace std;

InvalidLuaType::InvalidLuaType(LuaType expected)
{
	stringstream x;
	x << "Invalid Lua type, expected: ";
	x << getTypeString(expected);

	msg = x.str();
}

InvalidLuaType::InvalidLuaType(LuaType expected, LuaType actual)
{
	stringstream x;
	x << "Invalid Lua type, expected: ";
	x << getTypeString(expected);
	x << ", got: " << getTypeString(actual);

	msg = x.str();
}

const char* InvalidLuaType::what()
{
	return msg.c_str();
}