#include "LuaState.hpp"
#include "LuaType.hpp"

LuaState::LuaState(bool openLibs) :
	L(luaL_newstate()),
	push(L),
	to(L)
{
	
}

void LuaState::pop(int n)
{
	lua_pop(L, n);
}


LuaType LuaState::getType(int idx)
{
	return convertLuaType(lua_type(L, idx));
}
