#pragma once
#include "lua.hpp"

int nativeFunc(lua_State* L)
{
	lua_Integer a = lua_tointeger(L, 1);
	lua_Integer b = lua_tointeger(L, 2);

	lua_pushinteger(L, a + b);
	return 1;
}

int main()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	luaL_loadfile(L, "test.lua");
	lua_register(L, "nativeFunc", nativeFunc);

	lua_getglobal(L, "scriptFunc");
	lua_pcall(L, 0, 0, 0);

	return 0;
}