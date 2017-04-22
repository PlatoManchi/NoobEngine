#include "Events/EventSubscriber.h"
#include "Events/EventQueue.h"
#include "Events/Event.h"

using namespace NoobEngine::Events;
using namespace std;

namespace SupportingClasses
{
	class ClearQueueEventSubscriber : public NoobEngine::Events::EventSubscriber
	{
	public:

		ClearQueueEventSubscriber() {}

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override
		{
			Event<EventQueue*> *eventPtr = pPublisher.As<Event<EventQueue*>>();
			EventQueue* eventQueue = eventPtr->Message();

			eventQueue->Clear();
		}
	};

}