#pragma once

#include "HashedString/HashedString.h"

#include <string>

namespace Engine
{
	class IComponent
	{
	public:
		IComponent(const char* i_pName, const char* i_pType) :
			m_Name(i_pName),
			m_Type(i_pType)
		{}

		const HashedString& GetName() const { return m_Name; }
		const HashedString& GetType() const { return m_Type; }
	private:
		HashedString m_Name;
		HashedString m_Type;
	};

	class StringComponent : public IComponent
	{
	public:
		StringComponent(const char* i_pName, const std::string& i_pValue) :
			IComponent(i_pName, "String"),
			m_Value(i_pValue)
		{}
	private:
		std::string m_Value;
	};
}