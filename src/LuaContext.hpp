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

		template<LuaType T> void push();
		template<> void push<LuaType::NIL>();

		template<class T> void push(T v);
		template<> void push<bool>(bool b);
		template<> void push(LuaInt n);
		template<> void push(LuaNum n);
		template<> void push<void*>(void* p);

		void push_luaFunc(LuaCFunc func, int upvalues = 0);
		//void push_saturnFunc(SaturnFunc func);
		/*

		void push_fString(const char* format, ...);
		void push_cString(const char* s, int len = -1);
		void push_globalTable();

		void push_string(const std::string& s);
		//TODO pushthread
		//internally pushvalue
		void push_copy(int idx);
		void push_copy(int from, int to);
		void push_table(int arrayHint = 0, int dictHint = 0);
		//TODO newuserdata
		*/

		template<class T> T to(int idx);
		template<> LuaInt to(int idx);
		template<> LuaNum to(int idx);
		template<> bool to(int idx);
		template<> void* to(int idx);
		template<> const char* to(int idx);

		LuaCFunc to_luaFunc(int idx);

		//TODO tothread

		template<LuaType T> bool is(int idx);
		template<> bool is<LuaType::BOOL>(int idx);
		template<> bool is<LuaType::NIL>(int idx);
		template<> bool is<LuaType::NUMBER>(int idx);
		template<> bool is<LuaType::STRING>(int idx);;
		template<> bool is<LuaType::TABLE>(int idx);
		template<> bool is<LuaType::USERDATA>(int idx);
		template<> bool is<LuaType::LIGHTUSERDATA>(int idx);
		template<> bool is<LuaType::CFUNCTION>(int idx);
		template<> bool is<LuaType::THREAD>(int idx);

		//internally isLightUserData
		bool is_pointer(int idx);

		//internally isNone
		bool is_invalid(int idx);
		//internally isNoneOrNil
		bool is_invalidOrNil(int idx);
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
	
		explicit LuaContext(bool openLibs = true);
		explicit LuaContext(lua_State* L);

		~LuaContext();

		void pop(int n);

		void call(int numArgs = 0, int numReturns = LUA_MULTRET);

		void registerFunc(const std::string& name, LuaCFunc func);
		//void registerFunc(const std::string& name, SaturnFunc func);

		void close();

		void set_global(const std::string& name);
		LuaType get_global(const std::string& name);

		void load_stdLibs();
		void load_file(const std::string& filename, bool setup = true);
	};

}