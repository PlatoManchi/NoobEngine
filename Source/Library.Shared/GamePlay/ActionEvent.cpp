#include "pch.h"
#include "ActionEvent.h"
#include "Events/Event.h"
#include "Events/EventMessageAttributed.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionEvent)

		ActionEvent::ActionEvent() :
			Action()
		{
			Populate();
		}

		void ActionEvent::Update(WorldState& pWorldState)
		{
			Events::EventMessageAttributed msgAttribute;
			for (std::pair<std::string, Runtime::Datum> element : *this)
			{
				if (IsAuxiliaryAttribute(element.first))
				{
					msgAttribute.AppendAuxiliaryAttribute(element.first) = element.second;
				}
			}

			shared_ptr<Events::Event<Events::EventMessageAttributed>> eventTmp = make_shared<Events::Event<Events::EventMessageAttributed>>(msgAttribute);
			pWorldState.mCurrentWorld->GetEventQueue().Enqueue(eventTmp, pWorldState.mGameTime, mDelay);
		}

		std::string ActionEvent::GetSubtype() const
		{
			return mSubtype;
		}

		void ActionEvent::SetSubtype(const std::string& pSubtype)
		{
			mSubtype = pSubtype;
		}

		float ActionEvent::GetDelay() const
		{
			return mDelay;
		}

		void ActionEvent::SetDelay(float pDelay)
		{
			mDelay = pDelay;
		}

		void ActionEvent::Populate()
		{
			Action::Populate();

			AppendPrescribedAttribute("subtype").SetStorage(&mSubtype, 1);
			AppendPrescribedAttribute("delay").SetStorage(&mDelay, 1);
		}
	}
}