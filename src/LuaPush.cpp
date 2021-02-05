#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace std;
using namespace saturn;

constexpr int FUNC_PTR = 1;
constexpr int STATE_PTR = 2;

LuaContext::LuaPush::LuaPush(LuaContext* parent) :
	parent(parent)
{
	L = parent->L;
}

void LuaContext::LuaPush::boolean(bool b)
{
	lua_pushboolean(L, b);
}

void LuaContext::LuaPush::globalTable()
{
	lua_pushglobaltable(L);
}

void LuaContext::LuaPush::integer(LuaInt n)
{
	lua_pushinteger(L, n);
}

void LuaContext::LuaPush::pointer(void* p)
{
	lua_pushlightuserdata(L, p);
}

void LuaContext::LuaPush::nil()
{
	lua_pushnil(L);
}

void LuaContext::LuaPush::number(LuaNum n)
{
	lua_pushnumber(L, n);
}

void LuaContext::LuaPush::string(const std::string& s)
{
	lua_pushstring(L, s.c_str());
}

void LuaContext::LuaPush::fString(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	lua_pushvfstring(L, format, args);
}

void LuaContext::LuaPush::cString(const char* s, int len)
{
	if(len < 0)
	{
		lua_pushstring(L, s);
	}
	else
	{
		lua_pushlstring(L, s, len);
	}
}

void LuaContext::LuaPush::copy(int idx)
{
	lua_pushvalue(L, idx);
}

void LuaContext::LuaPush::copy(int from, int to)
{
	lua_copy(L, from, to);
}

void LuaContext::LuaPush::luaFunc(LuaCFunc func, int upvalues)
{
	lua_pushcclosure(L, func, upvalues);
}

void LuaContext::LuaPush::table(int arrayHint, int dictHint)
{
	lua_createtable(L, arrayHint, dictHint);
}

void LuaContext::LuaPush::saturnFunc(SaturnFunc func)
{
	lua_pushlightuserdata(L, this);
	lua_pushlightuserdata(L, func);

	lua_pushcclosure(L, callOverride, 2);
	//lua_pushcclosure(L, callOverride, 1);
}

int LuaContext::LuaPush::callOverride(lua_State* L)
{
	LuaContext* ctx = (LuaContext*)lua_touserdata(L, lua_upvalueindex(1));
	//LuaContext ctx(L);
	SaturnFunc func = (SaturnFunc)lua_touserdata(L, lua_upvalueindex(2));

	return func(*ctx);
}

int LuaContext::LuaPush::indexOverride(lua_State* L)
{
	//TOCHANGE indexoverride?
	//can just state that messing with these funcs 
	//causes undefined behavior
	return 0;
}
