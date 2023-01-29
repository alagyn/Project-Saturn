#include "LuaType.hpp"
#include <map>
#include <stdexcept>

using namespace saturn;

const std::map<LuaType, const char*> nameMap = {
	{LuaType::Nil, "Nil"},
	{LuaType::Bool, "Bool"},
	{LuaType::Number, "Number"},
	{LuaType::String, "String"},
	{LuaType::Function, "C Function"},
	{LuaType::Pointer, "Pointer"},
	{LuaType::Userdata, "UserData"},
	{LuaType::Thread, "Thread"},
	{LuaType::Table, "Table"}
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

//TODO remove
/* 
LuaType saturn::convertLuaType(int t)
{
	return static_cast<LuaType>(t);
}
*/
