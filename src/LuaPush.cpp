#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace std;
using namespace saturn;

constexpr int FUNC_PTR = 1;
constexpr int STATE_PTR = 2;

void LuaContext::push_boolean(bool b)
{
	lua_pushboolean(L, b);
}

void LuaContext::push_globalTable()
{
	lua_pushglobaltable(L);
}

void LuaContext::push_pointer(void* p)
{
	lua_pushlightuserdata(L, p);
}

void LuaContext::push_nil()
{
	lua_pushnil(L);
}

void LuaContext::push_number(LuaNum n)
{
	lua_pushnumber(L, n);
}

void LuaContext::push_string(const std::string& s)
{
	lua_pushstring(L, s.c_str());
}

void LuaContext::push_fString(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	lua_pushvfstring(L, format, args);
}

void LuaContext::push_cString(const char* s, int len)
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

void LuaContext::push_copy(int idx)
{
	lua_pushvalue(L, idx);
}

void LuaContext::push_copy(int from, int to)
{
	lua_copy(L, from, to);
}


void LuaContext::push_table(int arrayHint, int dictHint)
{
	lua_createtable(L, arrayHint, dictHint);
}

void LuaContext::push_integer(LuaInt n)
{
	lua_pushinteger(L, n);
}

void LuaContext::push_luaFunc(LuaCFunc func, int upvalues)
{
	lua_pushcclosure(L, func, upvalues);
}

void LuaContext::push_saturnFunc(SaturnFunc func)
{
	lua_pushlightuserdata(L, this);
	lua_pushlightuserdata(L, func);

	lua_pushcclosure(L, callOverride, 2);
	//lua_pushcclosure(L, callOverride, 1);
}

int LuaContext::callOverride(lua_State* L)
{
	LuaContext* ctx = (LuaContext*)lua_touserdata(L, lua_upvalueindex(1));
	//LuaContext ctx(L);
	SaturnFunc func = (SaturnFunc)lua_touserdata(L, lua_upvalueindex(2));

	return func(*ctx);
}

