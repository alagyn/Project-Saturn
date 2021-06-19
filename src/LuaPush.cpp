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

void LuaContext::push_luaFunc(LuaCFunc func, int upvalues)
{
	lua_pushcclosure(L, func, upvalues);
}

void LuaContext::push_saturnFunc(SaturnFunc func)
{
	lua_pushlightuserdata(L, this);
	lua_pushlightuserdata(L, func);

	lua_pushcclosure(L, callOverride, 2);
}

template<class T> void LuaContext::push(T val)
{
	throw LuaException("Invalid Datatype");
}

template<> void LuaContext::push<bool>(bool b)
{
	lua_pushboolean(L, b);
}

template<> void LuaContext::push<LuaType::NIL>()
{
	lua_pushnil(L);
}

template<> void LuaContext::push(LuaInt n)
{
	lua_pushinteger(L, n);
}

template<> void LuaContext::push(LuaNum n)
{
	lua_pushnumber(L, n);
}

template<> void LuaContext::push<void*>(void* p)
{
	lua_pushlightuserdata(L, p);

}

