#include "LuaState.hpp"
#include "LuaType.hpp"
#include "LuaExceptions.hpp"

LuaState::LuaState(bool openLibs) :
	L(luaL_newstate()),
	push(L),
	to(L),
	load(L),
	get(L)
{
	if(openLibs)
	{
		load.stdLibs();
	}
}

void LuaState::pop(int n)
{
	lua_pop(L, n);
}

LuaType LuaState::getType(int idx)
{
	return convertLuaType(lua_type(L, idx));
}

void LuaState::call(int numArgs, int numReturns)
{
	//TOCHANGE pull func name for errors?
	//TOCHANGE allow msg handlers?

	int error = lua_pcall(L, numArgs, numReturns, 0);

	if(error)
	{
		throw LuaCallError(lua_tostring(L, -1));
	}
}
