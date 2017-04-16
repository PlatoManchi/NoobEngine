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

			float health = (*player)["Health"].Get<float>();

			Assert::AreEqual(100.0f, health);
			
			Assert::IsTrue(worldSharedData.GetRootNode() == worldSharedData.GetCurrentNode());

			Assert::IsTrue(player->IsAttribute("action"));
			Assert::IsFalse(player->IsAttribute("reaction"));
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

			float health = (*player)["Health"].Get<float>();

			Assert::AreEqual(100.0f, health);

			Assert::IsTrue(player->IsAttribute("action"));
			Assert::IsFalse(player->IsAttribute("reaction"));
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ReactionTest::sStartMemState;
}