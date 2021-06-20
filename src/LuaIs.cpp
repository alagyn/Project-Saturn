#include "LuaContext.hpp"

using namespace saturn;


bool LuaContext::is_noneOrNil(int idx)
{
	return lua_type(L, idx) <= 0;
}

/*
bool LuaContext::is_yieldable()
{
	return lua_isyieldable(L);
}
*/

template<> bool LuaContext::is<LuaType::NONE>(int idx)
{
	return lua_type(L, idx) == LUA_TNONE;
}

template<> bool LuaContext::is<LuaType::BOOL>(int idx)
{
	return lua_type(L, idx) == LUA_TBOOLEAN;
}

template<> bool LuaContext::is<LuaType::NIL>(int idx)
{
	return lua_type(L, idx) == LUA_TNIL;
}

template<> bool LuaContext::is<LuaType::NUMBER>(int idx)
{
	return lua_isnumber(L, idx);
}

template<> bool LuaContext::is<LuaType::STRING>(int idx)
{
	return lua_isstring(L, idx);
}

template<> bool LuaContext::is<LuaType::TABLE>(int idx)
{
	return lua_type(L, idx) == LUA_TTABLE;
}

template<> bool LuaContext::is<LuaType::USERDATA>(int idx)
{
	return lua_isuserdata(L, idx);
}

template<> bool LuaContext::is<LuaType::POINTER>(int idx)
{
	return lua_type(L, idx) == LUA_TLIGHTUSERDATA;		
}

template<> bool LuaContext::is<LuaType::CFUNCTION>(int idx)
{
	return lua_iscfunction(L, idx);
}

template<> bool LuaContext::is<LuaType::THREAD>(int idx)
{
	return lua_type(L, idx) == LUA_TTHREAD;
}

template<> bool LuaContext::is<LuaType::SFUNCTION>(int idx)
{
	//TODO is SFUNC?
	return false;
}