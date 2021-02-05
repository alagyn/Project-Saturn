#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"

#define NO_INNER

//TOFIX Test constructor efficiency w/ and w/o inner classes
//TOFIX Test SaturnFunc efficiency vs vanilla
//TOFIX Test SaturnFunc storing pointers in table vs upvalues
//TOFIX Figure out how to let users have upvalues for SaturnFuncs
//TOFIX Figure out if LuaContext needs any state

//TOCHANGE change inner classes to be templates
//Instead of ctx.push.string("asdf")
//Do ctx.push<string>("asdf")
//Make template specializations for each
//Make default template throw an error for undefined operations

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
			/*
			void push_boolean(bool b);
			*/
			void push_luaFunc(LuaCFunc func, int upvalues = 0);
			void push_saturnFunc(SaturnFunc func);
			/*
			void push_fString(const char* format, ...);
			void push_cString(const char* s, int len = -1);
			void push_globalTable();
			*/
			void push_integer(LuaInt n);
			//Internally lightuserdata
			/*
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
			*/
	
			/*
		class LuaTo
		{
		private:
			lua_State* L;

		public:
			LuaTo(lua_State* L);

			bool boolean(int idx);
			LuaCFunc luaFunc(int idx);
			
			const char* string(int idx, size_t* lenOutput = nullptr);
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
			LuaIs(lua_State* L);
			
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

			//TODO equal?
			//rawequal
		};

		class LuaGet
		{
		private:
			lua_State* L;

		public:
			LuaGet(lua_State* L);

			//TODO LuaGet
			LuaType index(int tableIdx, LuaInt idx);
			LuaType key(int tableIdx, const std::string& key);
			//Uses top of stack as key, works for any object as key?
			LuaType key(int tableIdx);
			//Returns true if mt exists
			bool metatable(int tableIdx);
			LuaType type(int idx);
			void length(int idx);

			void rawLength(int idx);
			LuaType rawKey(int tableIdx);
			LuaType rawIndex(int tableIdx, LuaInt idx);

		};

		class LuaSet
		{
		private:
			lua_State* L;

		public:
			LuaSet(lua_State* L);

			void key(int tableIdx, const std::string& key);
			void key(int tableIdx);
			void index(int tableIdx, LuaInt idx);
			//TODO setiuservalue?
			void metatable(int tableIdx);

			void rawKey(int tableIdx);
			void rawIndex(int tableIdx, LuaInt idx);
		};

		class LuaStack
		{
		private:
			lua_State* L;

		public:
			LuaStack(lua_State* L);

			int absIndex(int idx);
			//internally checkstack
			bool ensure(int n);
			void close();
			int top();
			void top(int newTop);
			void insert(int idx);
			//TODO next?
			void remove(int idx);
			void replace(int idx);
			void rotate(int idx, int n);
			//TODO equal/ other comparisons?
		};
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
