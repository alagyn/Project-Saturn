#include "LuaContext.hpp"
#include "LuaType.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

LuaContext::LuaContext(lua_State* L):
	L(L),
	push(this),
	to(L),
	load(L),
	get(L),
	set(L),
	stack(L)
{
	
}

LuaContext::LuaContext(bool openLibs) :
	LuaContext(luaL_newstate())
{
	if(openLibs)
	{
		load.stdLibs();
	}
}

LuaContext::~LuaContext()
{
	lua_close(L);
}


void LuaContext::pop(int n)
{
	lua_pop(L, n);
}

void LuaContext::call(int numArgs, int numReturns)
{
	//TOCHANGE pull func name for errors?
	//TOCHANGE allow msg handlers?
	
	//TOCHANGE make an all in one call func
	//i.e. call("func", ArgList);

	int error = lua_pcall(L, numArgs, numReturns, 0);

	if(error)
	{
		throw LuaCallError(lua_tostring(L, -1));
	}
}

void LuaContext::registerFunc(const std::string& name, LuaCFunc func)
{
	lua_register(L, name.c_str(), func);
}

void LuaContext::registerFunc(const std::string& name, SaturnFunc func)
{
	push.saturnFunc(func);
	set.global(name);
}
