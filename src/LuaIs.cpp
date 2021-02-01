#include "LuaState.hpp"

using namespace saturn;

LuaState::LuaIs::LuaIs(lua_State* L):
	L(L)
{

}

bool LuaState::LuaIs::boolean(int idx)
{
	return lua_isboolean(L, idx);
}

bool LuaState::LuaIs::cFunction(int idx)
{
	return lua_iscfunction(L, idx);
}

bool LuaState::LuaIs::function(int idx)
{
	return lua_isfunction(L, idx);
}

bool LuaState::LuaIs::integer(int idx)
{
	return lua_isinteger(L, idx);
}

bool LuaState::LuaIs::pointer(int idx)
{
	return lua_islightuserdata(L, idx);
}

bool LuaState::LuaIs::nil(int idx)
{
	return lua_isnil(L, idx);
}

bool LuaState::LuaIs::invalid(int idx)
{
	return lua_isnone(L, idx);
}

bool LuaState::LuaIs::invalidOrNil(int idx)
{
	return lua_isnoneornil(L, idx);
}

bool LuaState::LuaIs::number(int idx)
{
	return lua_isnumber(L, idx);
}

bool LuaState::LuaIs::string(int idx)
{
	return lua_isstring(L, idx);
}

bool LuaState::LuaIs::table(int idx)
{
	return lua_istable(L, idx);
}

bool LuaState::LuaIs::thread(int idx)
{
	return lua_isthread(L, idx);
}

bool LuaState::LuaIs::userdata(int idx)
{
	return lua_isuserdata(L, idx);
}

bool LuaState::LuaIs::yieldable(int idx)
{
	return lua_isyieldable(L);
}