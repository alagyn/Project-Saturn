#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"

#define NO_INNER

//TOFIX Test constructor efficiency w/ and w/o inner classes
//TOFIX Figure out how to let users have upvalues for SaturnFuncs
//TOFIX Figure out if LuaContext needs any state

namespace saturn
{
	class LuaContext;

	using SaturnFunc = int (*)(LuaContext&);
	using LuaCFunc = int (*)(lua_State*);

	class LuaContext
	{
	private:
		lua_State* L;

		static int callOverride(lua_State* L);

	public:

		void push_boolean(bool b);
		void push_luaFunc(LuaCFunc func, int upvalues = 0);
		void push_saturnFunc(SaturnFunc func);

		void push_fString(const char* format, ...);
		void push_cString(const char* s, int len = -1);
		void push_globalTable();

		void push_integer(LuaInt n);
		//Internally lightuserdata
		void push_pointer(void* p);

		void push_nil();
		void push_number(LuaNum n);
		void push_string(const std::string& s);
		//TODO pushthread
		//internally pushvalue
		void push_copy(int idx);
		void push_copy(int from, int to);
		void push_table(int arrayHint = 0, int dictHint = 0);
		//TODO newuserdata

		bool to_boolean(int idx);
		LuaCFunc to_luaFunc(int idx);

		const char* to_string(int idx, size_t* lenOutput = nullptr);
		LuaNum to_number(int idx, bool unsafe = true);
		//internally touserdata
		void* to_pointer(int idx);
		//TODO tothread

		bool is_boolean(int idx);
		bool is_cFunction(int idx);
		bool is_function(int idx);
		bool is_integer(int idx);
		//internally isLightUserData
		bool is_pointer(int idx);
		bool is_nil(int idx);
		//internally isNone
		bool is_invalid(int idx);
		//internally isNoneOrNil
		bool is_invalidOrNil(int idx);
		bool is_number(int idx);
		bool is_string(int idx);
		bool is_table(int idx);
		bool is_thread(int idx);
		bool is_userdata(int idx);
		bool is_yieldable(int idx);

		//TODO equal?
		//rawequal

		//TODO LuaGet
		LuaType get_index(int tableIdx, LuaInt idx);
		LuaType get_key(int tableIdx, const std::string& key);
		//Uses top of stack as key, works for any object as key?
		LuaType get_key(int tableIdx);
		//Returns true if mt exists
		bool get_metatable(int tableIdx);
		LuaType get_type(int idx);
		void get_length(int idx);

		void get_rawLength(int idx);
		LuaType get_rawKey(int tableIdx);
		LuaType get_rawIndex(int tableIdx, LuaInt idx);

		void set_key(int tableIdx, const std::string& key);
		void set_key(int tableIdx);
		void set_index(int tableIdx, LuaInt idx);
		//TODO setiuservalue?
		void set_metatable(int tableIdx);
		void set_rawKey(int tableIdx);
		void set_rawIndex(int tableIdx, LuaInt idx);

		/*
		int stack_absIndex(int idx);
		//internally checkstack
		bool stack_ensure(int n);
		void stack_close();
		int stack_top();
		void stack_top(int newTop);
		void stack_insert(int idx);
		//TODO next?
		void stack_remove(int idx);
		void stack_replace(int idx);
		void stack_rotate(int idx, int n);
		//TODO equal/ other comparisons?
		*/

		/*
		class LuaLoader
		{
		public:
			LuaLoader(lua_State* L);

			void string(const std::string& s, bool setup = true);
		};
		*/
		//TODO LuaMetatableUtils?
		//TODO LuaArith?
		//TODO LuaGarbage?
		//TODO LuaThread?

		void callSetup();
	public:

		explicit LuaContext(bool openLibs = true);
		explicit LuaContext(lua_State* L);

		~LuaContext();

		void pop(int n);

		void call(int numArgs = 0, int numReturns = LUA_MULTRET);

		void registerFunc(const std::string& name, LuaCFunc func);
		void registerFunc(const std::string& name, SaturnFunc func);

		void close();

		void set_global(const std::string& name);
		LuaType get_global(const std::string& name);

		LuaInt to_integer(int idx, bool unsafe = true);

		void load_stdLibs();
		void load_file(const std::string& filename, bool setup = true);
	};
}