#include "LuaType.hpp"
#include <map>
#include <stdexcept>

using namespace saturn;

const std::map<LuaType, const char*> nameMap = {
	{LuaType::NIL, "Nil"},
	{LuaType::BOOL, "Bool"},
	{LuaType::NUMBER, "Number"},
	{LuaType::STRING, "String"},
	{LuaType::FUNCTION, "C Function"},
	{LuaType::POINTER, "Pointer"},
	{LuaType::USERDATA, "UserData"},
	{LuaType::THREAD, "Thread"},
	{LuaType::TABLE, "Table"}
};

const char* saturn::getTypeString(LuaType t)
{
	try
	{
		return nameMap.at(t);
	}
	catch(const std::out_of_range&)
	{
		return "Dev Error";
	}
}

LuaType saturn::convertLuaType(int t)
{
	return static_cast<LuaType>(t);
}
