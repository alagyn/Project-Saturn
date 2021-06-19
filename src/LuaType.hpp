#pragma once
#include <lua.hpp>

namespace saturn
{
	enum class LuaType
	{
		ERROR,
		NIL,
		BOOL,
		NUMBER,
		STRING,
		CFUNCTION,
		SFUNCTION,
		POINTER,
		LIGHTUSERDATA,
		USERDATA,
		THREAD,
		TABLE
	};

	LuaType convertLuaType(int t);
	const char* getTypeString(LuaType t);

	using LuaInt = lua_Integer;
	using LuaNum = lua_Number;
}