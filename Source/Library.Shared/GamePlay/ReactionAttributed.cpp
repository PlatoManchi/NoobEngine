#include "pch.h"
#include "ReactionAttributed.h"
#include "Events/Event.h"

using namespace NoobEngine::Events;

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ReactionAttributed)

		ReactionAttributed::ReactionAttributed() :
			Reaction()
		{
			Populate();


		}
		void ReactionAttributed::Update(WorldState& pWorldState)
		{
			Reaction::Update(pWorldState);
		}

		void ReactionAttributed::Notify(Events::EventPublisher& pPublisher)
		{
			Reaction::Notify(pPublisher);

			Event<EventMessageAttributed>* eventAttr = pPublisher.As<Event<EventMessageAttributed>>();
			
			if (eventAttr)
			{
				const EventMessageAttributed& msgAttributed = eventAttr->Message();
				if (msgAttributed.GetSubtype() == mSubtype)
				{
					for (std::pair<std::string, Runtime::Datum>& element : msgAttributed)
					{
						if (msgAttributed.IsAuxiliaryAttribute(element.first))
						{
							Append(element.first) = element.second;
						}
					}

					Update(*msgAttributed.GetWorld()->GetWorldState());
				}
			}
		}

		void ReactionAttributed::Populate()
		{
			Reaction::Populate();

			AppendPrescribedAttribute("subtype").SetStorage(&mSubtype, 1);
		}
	}
}