#include "LuaType.hpp"

using namespace saturn;

const char* saturn::getTypeString(LuaType t)
{
	switch(t)
	{
	case LuaType::ERROR:
		return "Invalid Index";
	case LuaType::NIL:
		return "Nil";
	case LuaType::BOOL:
		return "Bool";
	case LuaType::NUMBER:
		return "Number";
	case LuaType::STRING:
		return "String";
	case LuaType::FUNCTION:
		return "Function";
	case LuaType::POINTER:
		return "Pointer";
	case LuaType::USERDATA:
		return "UserData";
	case LuaType::THREAD:
		return "Thread";
	case LuaType::TABLE:
		return "Table";
	default:
		return "Dev Error";
	}
}

LuaType saturn::convertLuaType(int t)
{
	switch(t)
	{
	case LUA_TBOOLEAN:
		return LuaType::BOOL;
	case LUA_TFUNCTION:
		return LuaType::FUNCTION;
	case LUA_TLIGHTUSERDATA:
		return LuaType::POINTER;
	case LUA_TNIL:
		return LuaType::NIL;
	case LUA_TNUMBER:
		return LuaType::NUMBER;
	case LUA_TSTRING:
		return LuaType::STRING;
	case LUA_TTABLE:
		return LuaType::TABLE;
	case LUA_TTHREAD:
		return LuaType::THREAD;
	case LUA_TUSERDATA:
		return LuaType::USERDATA;
	default:
		return LuaType::ERROR;
	}
}
