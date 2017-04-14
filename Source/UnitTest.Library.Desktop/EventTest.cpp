#include "pch.h"
#include "CppUnitTest.h"
#include "GamePlay/GameTime.h"
#include "Events/Event.h"
#include "Events/EventQueue.h"
#include "Events/EventPublisher.h"
#include "SupportingClasses/EventMessageOne.h"
#include "SupportingClasses/EventMessageTwo.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::GamePlay;
using namespace NoobEngine::Events;
using namespace SupportingClasses;
using namespace std;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(EventTest)
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
				//Assert::Fail(L"Memory Leaks!");
			}
		}

		TEST_METHOD(DefaultConstructor)
		{
			// TODO: Your test code here
			EventQueue eventQueue;
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());
			
			//shared_ptr<EventPublisher> publisherOne = make_shared<Event<EventMessageOne>>();
			//shared_ptr<EventPublisher> publisherTwo = make_shared<Event<EventMessageTwo>>();

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());

			eventQueue.Update(gameTime);

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());

			eventQueue.Clear();

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());
		}

		TEST_METHOD(EnqueueTest)
		{
			EventQueue eventQueue;
			GameTime gameTime;
			gameTime.SetCurrentTime(std::chrono::high_resolution_clock::now());

			int tmpInt = 0;
			float tmpFloat = 1.0f;


			shared_ptr<Event<int>> publisherOne = make_shared<Event<int>>(tmpInt);
			shared_ptr<Event<float>> publisherTwo = make_shared<Event<float>>(tmpFloat);

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());

			eventQueue.Update(gameTime);

			// enquing
			eventQueue.Enqueue(publisherOne, gameTime);
			Assert::AreEqual(1U, eventQueue.Size());
			Assert::AreEqual(false, eventQueue.IsEmpty());

			eventQueue.Enqueue(publisherTwo, gameTime);
			Assert::AreEqual(2U, eventQueue.Size());
			Assert::AreEqual(false, eventQueue.IsEmpty());

			eventQueue.Clear();

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());
		}

		TEST_METHOD(SendTest)
		{
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

			publisherOne->Deliver();
			
			Assert::AreEqual(1, messageOne->mNotifiedCount);
			Assert::AreEqual(false, messageTwo->mIsNotified);


			publisherTwo->Deliver();
			
			Assert::AreEqual(1, messageOne->mNotifiedCount);
			Assert::AreEqual(true, messageTwo->mIsNotified);

			eventQueue.Clear();

			Assert::AreEqual(0U, eventQueue.Size());
			Assert::AreEqual(true, eventQueue.IsEmpty());
		}

		TEST_METHOD(UpdateTest)
		{
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
			gameTime.SetCurrentTime(gameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(1000.0f)) );
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
		}

		TEST_METHOD(CopySemantics)
		{
			// subscriber
			EventMessageOne messageOne = EventMessageOne();
			EventMessageOne messageOneCpy = messageOne;

			Assert::AreEqual(messageOne.mNotifiedCount, messageOneCpy.mNotifiedCount);
			
			EventMessageOne messageOneCpy2;
			messageOneCpy2 = messageOneCpy;

			Assert::AreEqual(messageOneCpy2.mNotifiedCount, messageOneCpy.mNotifiedCount);
			
			int tmpInt = 10;
			float tmpFloat = 1.0f;

			Event<int> publisherOne = Event<int>(tmpInt);
			Event<int> publisherOneCpy = publisherOne;
			Assert::AreEqual(publisherOne.IsExpired(), publisherOneCpy.IsExpired());
			Assert::AreEqual(publisherOne.Message(), publisherOneCpy.Message());

			int tmpInt2 = 13;
			Event<int> publisherOneCpy2(tmpInt2);
			publisherOneCpy2 = publisherOneCpy;
			Assert::AreEqual(publisherOneCpy2.IsExpired(), publisherOneCpy.IsExpired());
			Assert::AreEqual(publisherOneCpy2.Message(), publisherOneCpy.Message());

			Event<float> publisherTwo = Event<float>(tmpFloat);
			Event<float> publisherTwoCpy = publisherTwo;
			Assert::AreEqual(publisherTwo.IsExpired(), publisherTwoCpy.IsExpired());
			Assert::AreEqual(publisherTwo.Message(), publisherTwoCpy.Message());

			float tmpFloat2 = 13;
			Event<float> publisherTwoCpy2(tmpFloat2);
			publisherTwoCpy2 = publisherTwoCpy;
			Assert::AreEqual(publisherTwoCpy2.IsExpired(), publisherTwoCpy.IsExpired());
			Assert::AreEqual(publisherTwoCpy2.Message(), publisherTwoCpy.Message());
		}

		TEST_METHOD(MoveSemantics)
		{
			shared_ptr<EventMessageOne> messageOne = make_shared<EventMessageOne>();
			
			int tmpInt = 0;
			

			Event<int> publisherOne = Event<int>(tmpInt);
			
			Assert::AreEqual(0, messageOne->mNotifiedCount);
			
			// subscribing
			publisherOne.Subscribe(messageOne);
			

			Event<int> publisherMove(std::move(publisherOne));
			Assert::ExpectException<std::exception>([&] {publisherOne.Deliver(); });
			
			Assert::AreEqual(0, messageOne->mNotifiedCount);

			publisherMove.Deliver();

			Assert::AreEqual(1, messageOne->mNotifiedCount);

			Event<int> publisherMove2(tmpInt);

			publisherMove2 = std::move(publisherMove);
			Assert::ExpectException<std::exception>([&] {publisherMove.Deliver(); });

			publisherMove2.Deliver();

			Assert::AreEqual(2, messageOne->mNotifiedCount);
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EventTest::sStartMemState;
}