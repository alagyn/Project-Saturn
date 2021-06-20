#include "LuaType.hpp"
#include <map>
#include <stdexcept>

using namespace saturn;

const std::map<int, LuaType> convertMap = {
	{LUA_TBOOLEAN, LuaType::BOOL},
	{LUA_TFUNCTION, LuaType::CFUNCTION},
	{LUA_TLIGHTUSERDATA, LuaType::POINTER},
	{LUA_TNIL, LuaType::NIL},
	{LUA_TNUMBER, LuaType::NUMBER},
	{LUA_TSTRING, LuaType::STRING},
	{LUA_TTABLE, LuaType::TABLE},
	{LUA_TTHREAD, LuaType::THREAD},
	{LUA_TUSERDATA, LuaType::USERDATA}
};

const std::map<LuaType, const char*> nameMap = {
	{LuaType::NIL, "Nil"},
	{LuaType::BOOL, "Bool"},
	{LuaType::NUMBER, "Number"},
	{LuaType::STRING, "String"},
	{LuaType::CFUNCTION, "C Function"},
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
	catch(const std::out_of_range& e)
	{
		return "Dev Error";
	}
}

LuaType saturn::convertLuaType(int t)
{
	return convertMap.at(t);
}
