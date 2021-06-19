# Project-Saturn
A modern C++ wrapper for embedding Lua scripts

## Description
Project Saturn aims to create a modern, simplified API for embedding Lua into any project. 
It's main goals are to reduce typing and syntax errors as well as being friendly with IDE autocompletion.
It will also align more closely to modern C++ conventions and style. Saturn will also use strictly functions
no more messy macros.

Saturn is currently being built onto Lua version 5.4

## Examples
#### Standard Lua C/C++ API, while specifically avoiding any macros
```C++
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
```
#### Saturn API
```C++
#include "Saturn.hpp"

using namespace saturn;

int nativeFunc(LuaState& L)
{
	LuaInt a = L.to<LuaInt>(1);
	LuaInt b = L.to<LuaInt>(2);

	L.push<LuaInt>(a + b);
	
    return 1;
}

int main()
{
	LuaState L;

	L.load_file("test.lua");
	L.register_func("nativeFunc", nativeFunc);

	L.get_global("scriptFunc");
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
