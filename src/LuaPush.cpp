#include "LuaContext.hpp"
#include "LuaExceptions.hpp"

using namespace std;
using namespace saturn;

constexpr int FUNC_PTR = 1;
constexpr int STATE_PTR = 2;

int LuaContext::callOverride(lua_State* L)
{
	LuaContext* ctx = (LuaContext*)lua_touserdata(L, lua_upvalueindex(FUNC_PTR));
	//LuaContext ctx(L);
	SaturnFunc func = (SaturnFunc)lua_touserdata(L, lua_upvalueindex(STATE_PTR));

	return func(*ctx);
}

void LuaContext::push(LuaCFunc func, int upvalues)
{
	lua_pushcclosure(L, func, upvalues);
}

void LuaContext::push(SaturnFunc func)
{
	lua_pushlightuserdata(L, this);
	lua_pushlightuserdata(L, func);

	lua_pushcclosure(L, callOverride, 2);
}

void LuaContext::push_nil()
{
	lua_pushnil(L);
}

void LuaContext::push(bool b)
{
	lua_pushboolean(L, b);
}

void LuaContext::push(LuaInt n)
{
	lua_pushinteger(L, n);
}

void LuaContext::push(LuaNum n)
{
	lua_pushnumber(L, n);
}

 void LuaContext::push(void* p)
{
	lua_pushlightuserdata(L, p);

}

 void LuaContext::push(const std::string& s)
{
	lua_pushstring(L, s.c_str());
}

 void LuaContext::push(const char* s)
{
	lua_pushstring(L, s);
}

 void LuaContext::push(const char* s, size_t len)
 {
	 lua_pushlstring(L, s, len);
 }

void LuaContext::push_globalTable()
{
	lua_pushglobaltable(L);
}

void LuaContext::new_table(int arrayHint, int dictHint)
{
	lua_createtable(L, arrayHint, dictHint);
}

LuaThread LuaContext::new_thread()
{
	return lua_newthread(L);
}

void* LuaContext::new_userdata(size_t size, int numUValues)
{
	return lua_newuserdatauv(L, size, numUValues);
}