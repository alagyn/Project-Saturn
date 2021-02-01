#include "LuaState.hpp"
#include "LuaType.hpp"
#include "LuaExceptions.hpp"

LuaState::LuaState(lua_State* L):
	L(L),
	push(this),
	to(L),
	load(L),
	get(L),
	set(L),
	stack(L)
{
	
}

LuaState::LuaState(bool openLibs) :
	LuaState(luaL_newstate())
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
