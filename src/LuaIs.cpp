#include "LuaContext.hpp"

using namespace saturn;

bool LuaContext::is_pointer(int idx)
{
	return lua_islightuserdata(L, idx);
}

bool LuaContext::is_invalid(int idx)
{
	return lua_isnone(L, idx);
}

bool LuaContext::is_invalidOrNil(int idx)
{
	return lua_isnoneornil(L, idx);
}

bool LuaContext::is_yieldable(int idx)
{
	return lua_isyieldable(L);
}

template<> bool LuaContext::is<LuaType::BOOL>(int idx)
{
	return lua_isboolean(L, idx);
}

template<> bool LuaContext::is<LuaType::NIL>(int idx)
{
	return lua_isnil(L, idx);
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
	return lua_istable(L, idx);
}

template<> bool LuaContext::is<LuaType::USERDATA>(int idx)
{
	return lua_isuserdata(L, idx);
}

template<> bool LuaContext::is<LuaType::LIGHTUSERDATA>(int idx)
{
	return lua_islightuserdata(L, idx);
}

template<> bool LuaContext::is<LuaType::CFUNCTION>(int idx)
{
	return lua_islightuserdata(L, idx);
}

template<> bool LuaContext::is<LuaType::THREAD>(int idx)
{
	return lua_isthread(L, idx);
}