#include "pch.h"
#include "EventMessageAttributed.h"

namespace NoobEngine
{
	namespace Events
	{
		RTTI_DEFINITIONS(EventMessageAttributed)

		EventMessageAttributed::EventMessageAttributed() :
			Attribute(), mWorld(nullptr)
		{
			Populate();
		}

		std::string EventMessageAttributed::GetSubtype() const
		{
			return mSubtype;
		}

		void EventMessageAttributed::SetSubtype(const std::string& pSubtype)
		{
			mSubtype = pSubtype;
		}

		GamePlay::World* EventMessageAttributed::GetWorld() const
		{
			return mWorld;
		}

		void EventMessageAttributed::SetWorld(GamePlay::World& pWorld)
		{
			mWorld = &pWorld;
		}

		void EventMessageAttributed::Populate()
		{
			Attribute::Populate();

			AppendPrescribedAttribute("subtype").SetStorage(&mSubtype, 1);
		}
	}
}