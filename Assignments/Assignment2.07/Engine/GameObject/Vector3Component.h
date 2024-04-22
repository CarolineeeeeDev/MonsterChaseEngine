#pragma once

#include "Component.h"
#include "Math/Vector3.h"

namespace Engine
{
	class Vector3Component : public IComponent
	{
	public:
		Vector3Component(const char * i_pName, const Vector3& i_InitialValue = Vector3::Zero) :
			IComponent(i_pName, "Vector3"),
			m_Value(i_InitialValue)
		{}

		// get / set
		const Vector3& get() const { return m_Value; }
		void set(const Vector3& i_Value) { m_Value = i_Value; }

	private:
		Vector3 m_Value;
	};
}