#pragma once
#include <lua.hpp>
#include <string>
#include "LuaType.hpp"
#include <stdexcept>

//TOFIX Figure out how to let users have upvalues for SaturnFuncs
//TOFIX Figure out if LuaContext needs any state

namespace saturn
{
	class LuaContext;

	using SaturnFunc = int (*)(LuaContext&);
	using LuaCFunc = int (*)(lua_State*);

	using LuaThread = lua_State*;
	using LuaString = const char*;

	class LuaContext
	{
	private:
		lua_State* L;

		static int callOverride(lua_State* L);

	public:

		#pragma region PUSH

		void push(bool b);
		void push(LuaInt n);
		void push(LuaNum n);
		void push(const std::string& s);
		void push(char* s);
		void push(LuaCFunc func, int upvalues = 0);
		void push(SaturnFunc func);
		
		void push(void* p);

		void push_nil();
		void push_globalTable();
		void push_newTable(int arrayHint = 0, int dictHint = 0);
		LuaThread push_newThread();

		void* push_newUserData(size_t size, int numUValues = 1);

		#pragma endregion
		
		#pragma region TO

		template<class T> T to(int idx, int* ret = NULL)
		{
			throw std::logic_error("Template not defined");
		}

		template<> LuaInt to(int idx, int* ret);
		template<> LuaNum to(int idx, int* ret);
		template<> bool to(int idx, int* ret);
		template<> LuaString to(int idx, int* ret);
		template<> LuaCFunc to(int idx, int* ret);
		template<> void* to(int idx, int* ret);
		#pragma endregion

		#pragma region IS

		template<LuaType T> bool is(int idx);
		template<> bool is<LuaType::NONE>(int idx);
		template<> bool is<LuaType::BOOL>(int idx);
		template<> bool is<LuaType::NIL>(int idx);
		template<> bool is<LuaType::NUMBER>(int idx);
		template<> bool is<LuaType::STRING>(int idx);;
		template<> bool is<LuaType::TABLE>(int idx);
		template<> bool is<LuaType::USERDATA>(int idx);
		template<> bool is<LuaType::POINTER>(int idx);
		template<> bool is<LuaType::FUNCTION>(int idx);
		
		bool is_noneOrNil(int idx);
		bool is_yieldable(LuaThread t);

		#pragma endregion

		#pragma region GET

		LuaType get_index(int tableIdx, LuaInt idx);
		LuaType get_key(int tableIdx, const std::string& key);
		LuaType get_key(int tableIdx);
		
		bool get_metatable(int tableIdx);
		LuaType get_type(int idx);
		void get_length(int idx);

		void get_rawLength(int idx);
		LuaType get_rawKey(int tableIdx);
		LuaType get_rawIndex(int tableIdx, LuaInt idx);

		LuaType get_iUserVal(int udIdx, int n = 0);
		LuaType get_global(const std::string& name);

		#pragma endregion

		#pragma region SET

		void set_key(int tableIdx, const std::string& key);
		void set_key(int tableIdx);
		void set_index(int tableIdx, LuaInt idx);
		void set_metatable(int tableIdx);
		void set_raw(int tableIdx);
		void set_raw(int tableIdx, LuaInt idx);
		void set_raw(int tableIdx, const void* p);
		
		bool set_iUserVal(int udIdx, int n = 0);
		void set_global(const std::string& name);

		#pragma endregion

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

		//TODO LuaMetatableUtils?
		//TODO LuaArith?
		//TODO LuaGarbage?
		//TODO LuaThread?

		void initChunk();
	
		void pop(int n);

		void call(int numArgs = 0, int numReturns = LUA_MULTRET);

		void register_func(const std::string& name, LuaCFunc func);
		void register_func(const std::string& name, SaturnFunc func);

		//internally pushvalue
		void copy(int idx);
		//internally pushcopy
		void copy(int src, int dest);

		bool rawEqual(int idx1, int idx2);

		void close();

		void load_stdLibs();
		void load_file(const std::string& filename, bool init = true);
		void load_string(const std::string& s, bool init = true);

		explicit LuaContext(bool openLibs = true);
		explicit LuaContext(lua_State* L);

		~LuaContext();
	};

}