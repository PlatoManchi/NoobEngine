#include "pch.h"
#include "CppUnitTest.h"
#include "GamePlay/GameTime.h"
#include "Events/Event.h"
#include "Events/EventQueue.h"
#include "Events/EventPublisher.h"

#include "SupportingClasses/EventMessageOne.h"
#include "SupportingClasses/EventMessageTwo.h"
#include "SupportingClasses/EnqueueEventSubscriber.h"
#include "SupportingClasses/ClearQueueEventSubscriber.h"
#include "SupportingClasses/AddSubscriber.h"
#include "SupportingClasses/RemoveSubscriber.h"
#include "SupportingClasses/UnsubscribeAllSubscriber.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::GamePlay;
using namespace NoobEngine::Events;
using namespace SupportingClasses;
using namespace std;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(AsyncTest)
	{
	public:
		TEST_METHOD_INITIALIZE(Initialize)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF);
			_CrtMemCheckpoint(&sStartMemState);
		}

		TEST_METHOD_CLEANUP(Cleanup)
		{
			_CrtMemState endMemState, diffMemState;
			endMemState;
			diffMemState;
			_CrtMemCheckpoint(&endMemState);
			if (_CrtMemDifference(&diffMemState, &sStartMemState, &endMemState))
			{
				_CrtMemDumpStatistics(&diffMemState);
				Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(NormalEventNotifyTest)
		{
			// normal event firing
			// add event to eventqueue through subscriber
			// clear eventqueue through subscribers
			// add subscriber through subscriber
			// remove subscriber through subscriber
			// removeall subscriber through subscriber

			EventQueue eventQueue;
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			shared_ptr<EventMessageOne> messageOne = make_shared<EventMessageOne>();
			shared_ptr<EventMessageTwo> messageTwo = make_shared<EventMessageTwo>();

			int tmpInt = 0;
			float tmpFloat = 1.0f;


			shared_ptr<Event<int>> publisherOne = make_shared<Event<int>>(tmpInt);
			shared_ptr<Event<float>> publisherTwo = make_shared<Event<float>>(tmpFloat);

			Assert::AreEqual(0, messageOne->mNotifiedCount);
			Assert::AreEqual(false, messageTwo->mIsNotified);

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());

			eventQueue.Update(gameTime);

			Assert::AreEqual(0, messageOne->mNotifiedCount);
			Assert::AreEqual(false, messageTwo->mIsNotified);

			// subscribing
			publisherOne->Subscribe(messageOne);
			publisherTwo->Subscribe(messageTwo);

			// enqueing
			eventQueue.Enqueue(publisherOne, gameTime, 1.0f);
			eventQueue.Enqueue(publisherTwo, gameTime, 2.0f);

			// adding 1 second and running update
			gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(1000.0f)));
			eventQueue.Update(gameTime);

			Assert::AreEqual(1, messageOne->mNotifiedCount);
			Assert::AreEqual(false, messageTwo->mIsNotified);

			// adding 2 second and running update
			gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(3000.0f)));
			eventQueue.Update(gameTime);

			Assert::AreEqual(1, messageOne->mNotifiedCount);
			Assert::AreEqual(true, messageTwo->mIsNotified);


			eventQueue.Clear();

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());

			Event<EventQueue*>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
			Event<float>::UnsubscribeAll();
		}

		TEST_METHOD(EnqueueEventThroughSubscriber)
		{
			// add event to EventQueue through subscriber

			EventQueue* eventQueue = new EventQueue();
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			shared_ptr<Event<EventQueue*>> publisherEvent = make_shared<Event<EventQueue*>>(eventQueue);

			shared_ptr<EnqueueEventSubscriber> subscriberEnqueueEvent = make_shared<EnqueueEventSubscriber>(&gameTime);

			Assert::IsTrue(eventQueue->IsEmpty());

			// subscribing the subscriber
			Event<EventQueue*>::Subscribe(subscriberEnqueueEvent);

			// enqueuing the events 10000 times
			// when the event is enqueued, there is no telling when it will delivered and removed from the queue
			for (uint32_t i = 0u; i < 100000u; ++i)
			{
				// enqueuing
				eventQueue->Enqueue(publisherEvent, gameTime, 1.0f);

				Assert::IsFalse(eventQueue->IsEmpty());
				Assert::AreNotEqual(0u, eventQueue->Size());

				// adding 1 second and running update
				gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(5000.0f)));

				// the data return by the function can be random
				// calling this function jsut to show that the funcitons are thread safe and can be called while spawning threads
				// or even while threads are running
				eventQueue->Size();

				eventQueue->Update(gameTime);

				eventQueue->Size();
				// there is  no way of telling how the queue will look like at this point
			}
			
			// since all .get is called on future the threads will be finished by the time execution reaches this point.
			Assert::IsTrue(eventQueue->IsEmpty());
			Assert::AreEqual(0U, eventQueue->Size());

			delete eventQueue;

			Event<EventQueue*>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
			Event<float>::UnsubscribeAll();
		}

		TEST_METHOD(ClearEventQueueThroughSubscriber)
		{
			// clear EventQueue through subscriber

			EventQueue* eventQueue = new EventQueue();
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			shared_ptr<Event<EventQueue*>> publisherEvent = make_shared<Event<EventQueue*>>(eventQueue);

			shared_ptr<ClearQueueEventSubscriber> subscriberEnqueueEvent = make_shared<ClearQueueEventSubscriber>();

			Assert::IsTrue(eventQueue->IsEmpty());

			// subscribing the subscriber
			Event<EventQueue*>::Subscribe(subscriberEnqueueEvent);

			// enqueuing the events 10000 times
			// when the event is enqueued, there is no telling when it will delivered and removed from the queue
			for (uint32_t i = 0u; i < 100000u; ++i)
			{
				// enqueuing
				eventQueue->Enqueue(publisherEvent, gameTime, 1.0f);

				Assert::IsFalse(eventQueue->IsEmpty());
				Assert::AreNotEqual(0u, eventQueue->Size());

				// adding 1 second and running update
				gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(5000.0f)));

				// the data return by the function can be random
				// calling this function jsut to show that the funcitons are thread safe and can be called while spawning threads
				// or even while threads are running
				eventQueue->Size();

				eventQueue->Update(gameTime);

				Assert::IsTrue(eventQueue->IsEmpty());
				Assert::AreEqual(0U, eventQueue->Size());
			}

			// since all .get is called on future the threads will be finished by the time execution reaches this point.
			Assert::IsTrue(eventQueue->IsEmpty());
			Assert::AreEqual(0U, eventQueue->Size());

			delete eventQueue;

			Event<EventQueue*>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
			Event<float>::UnsubscribeAll();
		}

		TEST_METHOD(SubscribeThroughSubscriber)
		{
			// add subscriber through subscriber
			
			EventQueue* eventQueue = new EventQueue();
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			shared_ptr<Event<EventQueue*>> publisherEvent = make_shared<Event<EventQueue*>>(eventQueue);

			shared_ptr<AddSubscriber> subscribeThroughSubscriber = make_shared<AddSubscriber>();

			Assert::IsTrue(eventQueue->IsEmpty());

			// subscribing the subscriber
			Event<EventQueue*>::Subscribe(subscribeThroughSubscriber);

			// enqueuing the events 10000 times
			// when the event is enqueued, there is no telling when it will delivered and removed from the queue
			for (uint32_t i = 0u; i < 100000u; ++i)
			{
				// enqueuing
				eventQueue->Enqueue(publisherEvent, gameTime, 1.0f);

				Assert::IsFalse(eventQueue->IsEmpty());
				Assert::AreNotEqual(0u, eventQueue->Size());

				// adding 1 second and running update
				gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(5000.0f)));

				// the data return by the function can be random
				// calling this function jsut to show that the funcitons are thread safe and can be called while spawning threads
				// or even while threads are running
				eventQueue->Size();

				eventQueue->Update(gameTime);

				Assert::IsTrue(eventQueue->IsEmpty());
				Assert::AreEqual(0U, eventQueue->Size());
			}

			// since all .get is called on future the threads will be finished by the time execution reaches this point.
			Assert::IsTrue(eventQueue->IsEmpty());
			Assert::AreEqual(0U, eventQueue->Size());

			delete eventQueue;

			Event<EventQueue*>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
			Event<float>::UnsubscribeAll();
		}

		TEST_METHOD(UnSubscribeThroughSubscriber)
		{
			// add subscriber through subscriber

			EventQueue* eventQueue = new EventQueue();
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			shared_ptr<Event<EventQueue*>> publisherEvent = make_shared<Event<EventQueue*>>(eventQueue);

			shared_ptr<RemoveSubscriber> subscribeThroughSubscriber = make_shared<RemoveSubscriber>();
			subscribeThroughSubscriber->SetThisSharedPtr(subscribeThroughSubscriber);

			Assert::IsTrue(eventQueue->IsEmpty());

			// subscribing the subscriber
			Event<EventQueue*>::Subscribe(subscribeThroughSubscriber);

			// enqueuing the events 10000 times
			// when the event is enqueued, there is no telling when it will delivered and removed from the queue
			for (uint32_t i = 0u; i < 100000u; ++i)
			{
				// enqueuing
				eventQueue->Enqueue(publisherEvent, gameTime, 1.0f);

				Assert::IsFalse(eventQueue->IsEmpty());
				Assert::AreNotEqual(0u, eventQueue->Size());

				// adding 1 second and running update
				gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(5000.0f)));

				// the data return by the function can be random
				// calling this function jsut to show that the funcitons are thread safe and can be called while spawning threads
				// or even while threads are running
				eventQueue->Size();

				eventQueue->Update(gameTime);

				Assert::IsTrue(eventQueue->IsEmpty());
				Assert::AreEqual(0U, eventQueue->Size());
			}

			// since all .get is called on future the threads will be finished by the time execution reaches this point.
			Assert::IsTrue(eventQueue->IsEmpty());
			Assert::AreEqual(0U, eventQueue->Size());

			delete eventQueue;

			Event<EventQueue*>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
			Event<float>::UnsubscribeAll();
		}

		TEST_METHOD(UnSubscribeAllThroughSubscriber)
		{
			// add subscriber through subscriber

			EventQueue* eventQueue = new EventQueue();
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			shared_ptr<Event<EventQueue*>> publisherEvent = make_shared<Event<EventQueue*>>(eventQueue);

			shared_ptr<UnsubscriberAllSubscriber> subscribeThroughSubscriber = make_shared<UnsubscriberAllSubscriber>();
			
			Assert::IsTrue(eventQueue->IsEmpty());

			// subscribing the subscriber
			Event<EventQueue*>::Subscribe(subscribeThroughSubscriber);

			// enqueuing the events 10000 times
			// when the event is enqueued, there is no telling when it will delivered and removed from the queue
			for (uint32_t i = 0u; i < 100000u; ++i)
			{
				// enqueuing
				eventQueue->Enqueue(publisherEvent, gameTime, 1.0f);

				Assert::IsFalse(eventQueue->IsEmpty());
				Assert::AreNotEqual(0u, eventQueue->Size());

				// adding 1 second and running update
				gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(5000.0f)));

				// the data return by the function can be random
				// calling this function jsut to show that the funcitons are thread safe and can be called while spawning threads
				// or even while threads are running
				eventQueue->Size();

				eventQueue->Update(gameTime);

				Assert::IsTrue(eventQueue->IsEmpty());
				Assert::AreEqual(0U, eventQueue->Size());
			}

			// since all .get is called on future the threads will be finished by the time execution reaches this point.
			Assert::IsTrue(eventQueue->IsEmpty());
			Assert::AreEqual(0U, eventQueue->Size());

			delete eventQueue;

			Event<EventQueue*>::UnsubscribeAll();
			Event<int>::UnsubscribeAll();
			Event<float>::UnsubscribeAll();
		}

	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState AsyncTest::sStartMemState;
}