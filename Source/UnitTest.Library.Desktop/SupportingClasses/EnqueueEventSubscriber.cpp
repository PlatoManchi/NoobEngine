#include "pch.h"
#include "EnqueueEventSubscriber.h"
#include "EventMessageOne.h"
#include "EventMessageTwo.h"

using namespace NoobEngine::Events;
using namespace std;

namespace SupportingClasses
{
	EnqueueEventSubscriber::EnqueueEventSubscriber(NoobEngine::GamePlay::GameTime* pGameTime) :
		mGameTime(pGameTime)
	{
	}

	void EnqueueEventSubscriber::Notify(EventPublisher& pPublisher)
	{
		Event<EventQueue*> *eventPtr = pPublisher.As<Event<EventQueue*>>();
		EventQueue* eventQueue = eventPtr->Message();

		int tmpInt = 0;
		float tmpFloat = 1.0f;

		shared_ptr<Event<int>> publisherOne = make_shared<Event<int>>(tmpInt);
		shared_ptr<Event<float>> publisherTwo = make_shared<Event<float>>(tmpFloat);
		
		// enqueing
		eventQueue->Enqueue(publisherOne, *mGameTime, 1.0f);
		eventQueue->Enqueue(publisherTwo, *mGameTime, 2.0f);

		shared_ptr<EventMessageOne> messageOne = make_shared<EventMessageOne>();
		shared_ptr<EventMessageTwo> messageTwo = make_shared<EventMessageTwo>();

		// subscribing
		publisherOne->Subscribe(messageOne);
		publisherTwo->Subscribe(messageTwo);
	}
}