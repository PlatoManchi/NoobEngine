#include "pch.h"
#include "CppUnitTest.h"

#include "GamePlay/ReactionAttributed.h"
#include "GamePlay/WorldState.h"

#include "GamePlay/Entity.h"
#include "GamePlay/Sector.h"
#include "GamePlay/World.h"

#include "GamePlay/ActionDecrement.h"
#include "GamePlay/ActionEvent.h"

#include "Parsers/WorldSharedData.h"
#include "Parsers/WorldParseHelper.h"
#include "Parsers/ActionParseHelper.h"
#include "Parsers/ReactionParseHelper.h"
#include "Parsers/XmlParseMaster.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::GamePlay;
using namespace NoobEngine::Parsers;
using namespace NoobEngine::Events;
//using namespace SupportingClasses;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(ReactionTest)
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

		TEST_METHOD(ParsingTest)
		{
			EntityFactory entityFactory;
			ActionDecrementFactory decrementFactory;
			ActionEventFactory actionEventFactory;
			ReactionAttributedFactory reactionAttributedFactory;

			const char* xmlGrammar = "Resources/ReactionXml.xml";

			WorldSharedData worldSharedData;
			WorldParseHelper worldParseHelper;
			ActionParseHelper actionParseHelper;
			ReactionParseHelper reactionParseHelper;

			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);
			parser.AddHelper(actionParseHelper);
			parser.AddHelper(reactionParseHelper);

			parser.ParseFromFile(xmlGrammar);

			World* world = static_cast<World*>(&worldSharedData.GetRootNode());
			Sector* sector = static_cast<Sector*>((*world)[Sector::sSectorsKey].Get<NoobEngine::Runtime::Scope*>());
			Entity* player = static_cast<Entity*>((*sector)[Entity::sEntitiesKey].Get<NoobEngine::Runtime::Scope*>());

			int32_t health = (*player)["He"].Get<int32_t>();

			Assert::AreEqual(100, health);
			
			//Assert::IsTrue(&worldSharedData.GetRootNode() == &worldSharedData.GetCurrentNode());

			Assert::IsTrue(player->IsAttribute("action"));
			Assert::IsTrue(player->IsAttribute("reaction"));

			Event<EventMessageAttributed>::UnsubscribeAll();
		}

		TEST_METHOD(UpdateNotifyTest)
		{
			EntityFactory entityFactory;
			ActionDecrementFactory decrementFactory;
			ActionEventFactory actionEventFactory;
			ReactionAttributedFactory reactionAttributedFactory;

			const char* xmlGrammar = "Resources/ReactionXml.xml";

			WorldSharedData worldSharedData;
			WorldParseHelper worldParseHelper;
			ActionParseHelper actionParseHelper;
			ReactionParseHelper reactionParseHelper;

			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);
			parser.AddHelper(actionParseHelper);
			parser.AddHelper(reactionParseHelper);

			parser.ParseFromFile(xmlGrammar);

			World* world = static_cast<World*>(&worldSharedData.GetRootNode());
			Sector* sector = static_cast<Sector*>((*world)[Sector::sSectorsKey].Get<NoobEngine::Runtime::Scope*>());
			Entity* player = static_cast<Entity*>((*sector)[Entity::sEntitiesKey].Get<NoobEngine::Runtime::Scope*>());

			int32_t health = (*player)["He"].Get<int32_t>();
			Assert::AreEqual(100, health);

			// calling update
			WorldState worldState;
			worldState.mCurrentWorld = world;

			world->Update(worldState);

			health = (*player)["He"].Get<int32_t>();
			Assert::AreEqual(100, health);

			// adding 11 seconds
			worldState.mGameTime.SetCurrentTime(worldState.mGameTime.CurrentTime() + std::chrono::duration_cast<std::chrono::system_clock::duration>(std::chrono::duration<float>(11000.0f)));
			
			world->Update(worldState);

			health = (*player)["He"].Get<int32_t>();
			Assert::AreEqual(99, health);

			Event<EventMessageAttributed>::UnsubscribeAll();
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionTest::sStartMemState;
}