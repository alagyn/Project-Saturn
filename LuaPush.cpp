#include "LuaState.hpp"
#include "LuaExceptions.hpp"

using namespace std;
using namespace saturn;

constexpr int FUNC_PTR = 1;
constexpr int STATE_PTR = 2;

LuaState::LuaPush::LuaPush(LuaState* parent) :
	parent(parent)
{
	L = parent->L;
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

void LuaState::LuaPush::luaFunc(LuaCFunc func)
{
	lua_pushcfunction(L, func);
}

void LuaState::LuaPush::table(int arrayHint, int dictHint)
{
	lua_createtable(L, arrayHint, dictHint);
}

void LuaState::LuaPush::saturnFunc(SaturnFunc func)
{
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

int LuaState::LuaPush::callOverride(lua_State* L)
{
	//Get state
	lua_rawgeti(L, 1, STATE_PTR);
	LuaState* state = (LuaState*)lua_touserdata(L, -1);
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

int LuaState::LuaPush::indexOverride(lua_State* L)
{
	//TOCHANGE indexoverride?
	//can just state that messing with these funcs 
	//causes undefined behavior
	return 0;
}
