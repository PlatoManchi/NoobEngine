#include "Events/EventSubscriber.h"
#include "Events/EventQueue.h"
#include "Events/Event.h"

using namespace NoobEngine::Events;
using namespace std;

namespace SupportingClasses
{
	class UnsubscriberAllSubscriber : public NoobEngine::Events::EventSubscriber
	{
	public:

		UnsubscriberAllSubscriber()
		{
		}

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override
		{
			pPublisher;
			Event<EventQueue*>::UnsubscribeAll();
		}
	};
}