#include "lua.hpp"
#include "LuaContext.hpp"
#include "LuaType.hpp"
#include "LuaExceptions.hpp"

using namespace saturn;

LuaContext::LuaContext(lua_State* L):
	L(L)
{
	
}

LuaContext::LuaContext(bool openLibs) :
	LuaContext(luaL_newstate())
{
	if(openLibs)
	{
		load_stdLibs();
	}
}

LuaContext::~LuaContext()
{
	//lua_close(L);
}

void LuaContext::close()
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

void LuaContext::register_func(const std::string& name, LuaCFunc func)
{
	lua_register(L, name.c_str(), func);
}

void LuaContext::register_func(const std::string& name, SaturnFunc func)
{
	push(func);
	set_global(name);
}

void LuaContext::copy(int idx)
{
	lua_pushvalue(L, idx);
}

void LuaContext::copy(int src, int dest)
{
	lua_copy(L, src, dest);
}

bool LuaContext::rawEqual(int idx1, int idx2)
{
	return (bool)lua_rawequal(L, idx1, idx2);
}