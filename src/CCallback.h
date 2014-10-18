#pragma once

#include "CSingleton.h"
#include "sdk.h"

#include <string>
#include <queue>
#include <functional>
#include <stack>
#include <unordered_set>
#include <boost/variant.hpp>

#include <memory>

using std::string;
using std::queue;
using std::function;
using std::stack;
using std::unordered_set;
using boost::variant;

using std::shared_ptr;


class CCallback 
{
public: //type definitions
	using Type_t = shared_ptr<CCallback>;
	using ParamList_t = stack<variant<cell, string>>;

	//TODO: errors!!!
	enum class Errors
	{
		EMPTY_NAME,
		EMPTY_PARAMETERS,
		INVALID_AMX,
		NOT_FOUND,
		INVALID_PARAM_OFFSET,
		INVALID_FORMAT_SPECIFIER
	};


public: //constructor / destructor
	CCallback(AMX *amx, int cb_idx, ParamList_t &&params) :
		m_AmxInstance(amx),
		m_AmxCallbackIndex(cb_idx),
		m_Params(params)
	{

	}
	~CCallback() = default;


private: //variables
	AMX *m_AmxInstance = nullptr;
	int m_AmxCallbackIndex = -1;

	ParamList_t m_Params;
	bool m_Executed = false;

	
public: //functions
	bool Execute();
	

public: //factory function
	static Type_t Create(AMX *amx, string name, string format, cell *params, cell param_offset
		/*error_condition &error*/);
};


class CCallbackManager : public CSingleton<CCallbackManager>
{
	friend class CSingleton<CCallbackManager>;
private: //constructor / destructor
	CCallbackManager() = default;
	~CCallbackManager() = default;


private: //variables
	unordered_set<const AMX *> m_AmxInstances;


public: //functions
	inline bool IsValidAmx(const AMX *amx)
	{
		return m_AmxInstances.count(amx) == 1;
	}

	void AddAmx(const AMX *amx)
	{
		m_AmxInstances.insert(amx);
	}
	void RemoveAmx(const AMX *amx)
	{
		m_AmxInstances.erase(amx);
	}

};
