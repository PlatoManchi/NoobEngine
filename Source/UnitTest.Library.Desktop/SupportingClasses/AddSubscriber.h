#include "Events/EventSubscriber.h"
#include "Events/EventQueue.h"
#include "Events/Event.h"

using namespace NoobEngine::Events;
using namespace std;

namespace SupportingClasses
{
	class AddSubscriber : public NoobEngine::Events::EventSubscriber
	{
	public:

		AddSubscriber() {}

		void Notify(NoobEngine::Events::EventPublisher& pPublisher) override
		{
			pPublisher;
			shared_ptr<AddSubscriber> subscribeThroughSubscriber = make_shared<AddSubscriber>();
			Event<EventQueue*>::Subscribe(subscribeThroughSubscriber);
		}
	};

}