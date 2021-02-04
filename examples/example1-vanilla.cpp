#pragma once
#include "lua.hpp"

int nativeFunc(lua_State* L)
{
	//Pull first argument from stack
	lua_Integer a = lua_tointegerx(L, 1, nullptr);
	//Pull second
	lua_Integer b = lua_tointegerx(L, 2, nullptr);
	//Sum and push on to top of stack
	lua_pushinteger(L, a + b);
	//Return number of returns on stack
	return 1;
}

int main()
{
	//Make new context
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);

	//Load the file
	luaL_loadfilex(L, "test.lua", nullptr);

	//Push the native function
	lua_pushcclosure(L, nativeFunc, 0);
	//Set to global name
	lua_setglobal(L, "nativeFunc");

	//Get a global scoped script func
	lua_getglobal(L, "scriptFunc");

	//Call function with no args, and no returns
	lua_pcallk(L, 0, 0, 0, 0, 0);

	return 0;
}