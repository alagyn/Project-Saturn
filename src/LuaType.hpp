#pragma once
#include <lua.hpp>

namespace saturn
{
	enum class LuaType
	{
		None = LUA_TNONE,
		Nil = LUA_TNIL,
		Bool = LUA_TBOOLEAN,
		Number = LUA_TNUMBER,
		String = LUA_TSTRING,
		Function = LUA_TFUNCTION,
		Pointer = LUA_TLIGHTUSERDATA,
		Userdata = LUA_TUSERDATA,
		Thread = LUA_TTHREAD,
		Table = LUA_TTABLE
	};

	//LuaType convertLuaType(int t);
	const char* getTypeString(LuaType t);

}