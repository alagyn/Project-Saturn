#pragma once
#include <lua.hpp>

namespace saturn
{
	enum class LuaType
	{
		NONE = LUA_TNONE,
		NIL = LUA_TNIL,
		BOOL = LUA_TBOOLEAN,
		NUMBER = LUA_TNUMBER,
		STRING = LUA_TSTRING,
		FUNCTION = LUA_TFUNCTION,
		POINTER = LUA_TLIGHTUSERDATA,
		USERDATA = LUA_TUSERDATA,
		THREAD = LUA_TTHREAD,
		TABLE = LUA_TTABLE
	};

	//LuaType convertLuaType(int t);
	const char* getTypeString(LuaType t);

	using LuaInt = lua_Integer;
	using LuaNum = lua_Number;

}