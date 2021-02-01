#include "LuaState.hpp"

using namespace std;

LuaState::LuaPush::LuaPush(lua_State* L) :
	L(L)
{

}

void LuaState::LuaPush::boolean(bool b)
{
	lua_pushboolean(L, b);
}

void LuaState::LuaPush::globalTable()
{
	lua_pushglobaltable(L);
}

void LuaState::LuaPush::integer(LuaInt n)
{
	lua_pushinteger(L, n);
}

void LuaState::LuaPush::pointer(void* p)
{
	lua_pushlightuserdata(L, p);
}

void LuaState::LuaPush::nil()
{
	lua_pushnil(L);
}

void LuaState::LuaPush::number(LuaNum n)
{
	lua_pushnumber(L, n);
}

void LuaState::LuaPush::string(const std::string& s)
{
	lua_pushstring(L, s.c_str());
}

void LuaState::LuaPush::copy(int idx)
{
	lua_pushvalue(L, idx);
}

void LuaState::LuaPush::copy(int from, int to)
{
	lua_copy(L, from, to);
}

void LuaState::LuaPush::cFunction(LuaCFunc func)
{
	lua_pushcfunction(L, func);
}

void LuaState::LuaPush::table(int arrayHint, int dictHint)
{
	lua_createtable(L, arrayHint, dictHint);
}
