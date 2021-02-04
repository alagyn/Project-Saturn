#include "LuaState.hpp"
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
	//TODO figure out how to do upvalues

	//create psuedo-func table
	lua_createtable(L, 2, 0);
	//Save func pointer
	lua_pushlightuserdata(L, func);
	lua_rawseti(L, -2, FUNC_PTR);
	//Save state pointer
	lua_pushlightuserdata(L, parent);
	lua_rawseti(L, -2, STATE_PTR);

	//create metatable
	lua_createtable(L, 0, 0);
	//override __call method
	lua_pushstring(L, "__call");
	lua_pushcfunction(L, callOverride);
	lua_settable(L, -3);
	//TOCHANGE hide metatable?

	//Insert metatable in psuedo-func
	lua_setmetatable(L, -2);
}

int LuaContext::LuaPush::callOverride(lua_State* L)
{
	//Get state
	lua_rawgeti(L, 1, STATE_PTR);
	LuaContext* state = (LuaContext*)lua_touserdata(L, -1);
	//get function
	lua_rawgeti(L, 1, FUNC_PTR);
	SaturnFunc func = (SaturnFunc)lua_touserdata(L, -1);
	//Remove pointers from stack
	lua_pop(L, 2);
	//remove table, shifts user args to correct position
	lua_remove(L, 1);
	//Call function
	return func(*state);
}

int LuaContext::LuaPush::indexOverride(lua_State* L)
{
	//TOCHANGE indexoverride?
	//can just state that messing with these funcs 
	//causes undefined behavior
	return 0;
}
