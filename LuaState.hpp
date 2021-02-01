#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"
#include <unordered_map>

class LuaState;

using SaturnFunc = int (*)(LuaState*);
using LuaCFunc = int (*)(lua_State*);

class LuaState
{
private:
	lua_State* L;
	
	LuaState(lua_State* L);
	void makeModules();


	class LuaPush
	{
	private:
		lua_State* L;

	public:
		LuaPush(lua_State* L = nullptr);

		void boolean(bool b);
		void cFunction(LuaCFunc func);
		//TODO cClosure
		//TODO fString
		void globalTable();
		void integer(LuaInt n);
		//Internally lightuserdata
		void pointer(void* p);
		//TODO pushliteral
		//TODO pushlstring
		void nil();
		void number(LuaNum n);
		void string(const std::string& s);
		//TODO pushthread
		//internally pushvalue
		void copy(int idx);
		void copy(int from, int to);
		//TODO vfstring
		void table(int arrayHint = 0, int dictHint = 0);
		//TODO newuserdata
	};

	class LuaTo
	{
	private:
		lua_State* L;

	public:
		LuaTo(lua_State* L = nullptr);

		bool boolean(int idx);
		//TODO toCFunc
		LuaInt integer(int idx, bool unsafe = true);
		//TODO look at tolstring & tostring
		LuaNum number(int idx, bool unsafe = true);
		//internally touserdata
		void* pointer(int idx);
		//TODO tothread

	};

	class LuaIs
	{
	private:
		lua_State* L;

	public:
		LuaIs(lua_State* L = nullptr);

		bool boolean(int idx);
		bool cFunction(int idx);
		bool function(int idx);
		bool integer(int idx);
		//internally isLightUserData
		bool pointer(int idx);
		bool nil(int idx);
		//internally isNone
		bool invalid(int idx);
		//internally isNoneOrNil
		bool invalidOrNil(int idx);
		bool number(int idx);
		bool string(int idx);
		bool table(int idx);
		bool thread(int idx);
		bool userdata(int idx);
		bool yieldable(int idx);
	};

	class LuaGet
	{
	private:
		lua_State* L;

	public:
		LuaGet(lua_State* L = nullptr);

		//TODO LuaGet
		LuaType global(const std::string& name);
		LuaType index(int tableIdx, LuaInt idx);
		LuaType key(int tableIdx, const std::string& key);
		//Uses top of stack as key, works for any object as key?
		LuaType key(int tableIdx);
		//Returns true if mt exists
		bool metatable(int tableIdx);
	};

	class LuaStack
	{
	private:
		lua_State* L;

	public:
		LuaStack(lua_State* L = nullptr);

		//TODO top()
		//TODO checkstack
		//TODO absindex
		//TODO insert
	};
	
	class LuaLoader
	{
	private:
		lua_State* L;

		void callSetup();

	public:
		LuaLoader(lua_State* L = nullptr);

		void stdLibs();
		void file(const std::string& filename, bool setup = true);
		void string(const std::string& s, bool setup = true);
	};

public:
	
	LuaPush push;
	LuaTo to;
	LuaLoader load;
	LuaGet get;
	LuaStack stack;

	explicit LuaState(bool openLibs = true);
	
	void pop(int n);
	LuaType getType(int idx);

	void call(int numArgs = 0, int numReturns = LUA_MULTRET);

};
