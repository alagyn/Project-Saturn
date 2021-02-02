# Project-Saturn
A modern C++ wrapper for embedding Lua scripts

## Description
Project Saturn aims to create a modern, simplified API for embedding Lua into any project. 
It's main goals are to reduce typing and syntax errors as well as being friendly with IDE autocompletion.
It will also align more closely to modern C++ conventions and style. Saturn will also use strictly functions
no more messy macros.

Saturn is currently being built onto Lua version 5.4

## Examples
#### Standard Lua C/C++ API
```C++
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
```
#### Saturn API
```C++
#include "Saturn.hpp"

using namespace saturn;

int nativeFunc(LuaState& L)
{
	LuaInt a = L.to.integer(1);
	LuaInt b = L.to.integer(2);

	L.push.integer(a + b);
	return 1;
}

int main()
{
	LuaState L;

	L.load.file("test.lua");
	L.registerFunc("nativeFunc", nativeFunc);

	L.get.global("scriptFunc");
	L.call();
	return 0;
}
```

## API
Coming soon!


## What the name means
Saturn is an acronym for "Snakes Are The Underrated Reptile Narwhal"...


Just kidding, Project Saturn gets it's name from the Saturn V launch vehicle,
the first rocket to allow crewed missions to reach the moon (or Lua, in Portuguese).


And I just think that Saturn has a nice __*ring*__ to it.
