#include "LuaContext.hpp"

using namespace saturn;

LuaContext::LuaIs::LuaIs(lua_State* L):
	L(L)
{

}

bool LuaContext::LuaIs::boolean(int idx)
{
	return lua_isboolean(L, idx);
}

bool LuaContext::LuaIs::cFunction(int idx)
{
	return lua_iscfunction(L, idx);
}

bool LuaContext::LuaIs::function(int idx)
{
	return lua_isfunction(L, idx);
}

bool LuaContext::LuaIs::integer(int idx)
{
	return lua_isinteger(L, idx);
}

bool LuaContext::LuaIs::pointer(int idx)
{
	return lua_islightuserdata(L, idx);
}

bool LuaContext::LuaIs::nil(int idx)
{
	return lua_isnil(L, idx);
}

bool LuaContext::LuaIs::invalid(int idx)
{
	return lua_isnone(L, idx);
}

bool LuaContext::LuaIs::invalidOrNil(int idx)
{
	return lua_isnoneornil(L, idx);
}

bool LuaContext::LuaIs::number(int idx)
{
	return lua_isnumber(L, idx);
}

bool LuaContext::LuaIs::string(int idx)
{
	return lua_isstring(L, idx);
}

bool LuaContext::LuaIs::table(int idx)
{
	return lua_istable(L, idx);
}

bool LuaContext::LuaIs::thread(int idx)
{
	return lua_isthread(L, idx);
}

bool LuaContext::LuaIs::userdata(int idx)
{
	return lua_isuserdata(L, idx);
}

bool LuaContext::LuaIs::yieldable(int idx)
{
	return lua_isyieldable(L);
}