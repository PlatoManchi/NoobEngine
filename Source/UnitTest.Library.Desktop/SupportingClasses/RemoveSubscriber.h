#include "Events/EventSubscriber.h"
#include "Events/EventQueue.h"
#include "Events/Event.h"

using namespace NoobEngine::Events;
using namespace std;

namespace SupportingClasses
{
	class RemoveSubscriber : public NoobEngine::Events::EventSubscriber
	{
	public:

		RemoveSubscriber()
		{}

		void SetThisSharedPtr(shared_ptr<RemoveSubscriber> pThisPtr)
		{
			mThisSharedPointer = pThisPtr;
		}

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override
		{
			pPublisher;
			Event<EventQueue*>::Unsubscribe(mThisSharedPointer);
		}

		shared_ptr<RemoveSubscriber> mThisSharedPointer;
	};
}