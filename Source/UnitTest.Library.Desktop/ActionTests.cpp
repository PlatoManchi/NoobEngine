#include "pch.h"
#include "CppUnitTest.h"
#include "SupportingClasses/ActionPlayerAlive.h"
#include "SupportingClasses/ActionPlayerDead.h"

#include "GamePlay/Entity.h"

#include "Parsers/WorldSharedData.h"
#include "Parsers/WorldParseHelper.h"
#include "Parsers/ActionParseHelper.h"
#include "Parsers/XmlParseMaster.h"
#include "GamePlay/WorldState.h"
#include "GamePlay/Sector.h"

#include "GamePlay/World.h"
#include "GamePlay/ActionListIf.h"
#include "GamePlay/ActionDecrement.h"
#include "SupportingClasses\ActionTest.h"
#include "SupportingClasses\ActionTest.h"
#include "GamePlay\ActionCreateAction.h"
#include "GamePlay\ActionDestroyAction.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::GamePlay;
using namespace SupportingClasses;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(ActionTests)
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

		TEST_METHOD(DecrementActionTest)
		{
			EntityFactory factory;
			ActionDecrementFactory decrementFactory;

			const char* xmlGrammar = "Resources/DecrementActionXml.xml";

			NoobEngine::Parsers::WorldSharedData worldSharedData;
			NoobEngine::Parsers::WorldParseHelper worldParseHelper;
			NoobEngine::Parsers::ActionParseHelper actionParseHelper;

			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);
			parser.AddHelper(actionParseHelper);

			parser.ParseFromFile(xmlGrammar);

			World* world = reinterpret_cast<World*>(&worldSharedData.GetRootNode());
			Sector* sector = reinterpret_cast<Sector*>( (*world)[NoobEngine::GamePlay::Sector::sSectorsKey].Get<NoobEngine::Runtime::Scope*>());
			Entity* player = reinterpret_cast<Entity*>((*sector)[NoobEngine::GamePlay::Entity::sEntitiesKey].Get<NoobEngine::Runtime::Scope*>());

			int32_t lifeCount = (*player)["LifeCount"].Get<int32_t>();

			Assert::AreEqual(3, lifeCount);

			WorldState worldState;
			
			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(2, lifeCount);
			
			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(1, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(0, lifeCount);

			delete &worldSharedData.GetRootNode();
		}

		TEST_METHOD(ActionIfTest)
		{
			EntityFactory factory;
			ActionListIfFactory ifFactory;
			ActionPlayerAliveFactory aliveFactory;
			ActionPlayerDeadFactory deadFactory;
			ActionDecrementFactory decrementFactory;
			ActionTestFactory actiontestFactory;
			ActionCreateActionFactory createActionactory;
			ActionDestroyActionFactory destroyActionFactory;

			const char* xmlGrammar = "Resources/ActionIfXml.xml";

			NoobEngine::Parsers::WorldSharedData worldSharedData;
			NoobEngine::Parsers::WorldParseHelper worldParseHelper;
			NoobEngine::Parsers::ActionParseHelper actionParseHelper;

			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);
			parser.AddHelper(actionParseHelper);

			parser.ParseFromFile(xmlGrammar);

			World* world = reinterpret_cast<World*>(&worldSharedData.GetRootNode());

			// calling update
			WorldState worldState;
			worldState.mCurrentWorld = world;

			Sector* sector = reinterpret_cast<Sector*>((*world)[NoobEngine::GamePlay::Sector::sSectorsKey].Get<NoobEngine::Runtime::Scope*>());
			Entity* player = reinterpret_cast<Entity*>((*sector)[NoobEngine::GamePlay::Entity::sEntitiesKey].Get<NoobEngine::Runtime::Scope*>());

			int32_t lifeCount = (*player)["LifeCount"].Get<int32_t>();

			Assert::AreEqual(3, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(2, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(1, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(0, lifeCount);



			delete &worldSharedData.GetRootNode();
		}

		TEST_METHOD(TotalXmlTest)
		{
			EntityFactory factory;
			ActionListIfFactory ifFactory;
			ActionPlayerAliveFactory aliveFactory;
			ActionPlayerDeadFactory deadFactory;
			ActionDecrementFactory decrementFactory;
			ActionTestFactory actiontestFactory;
			ActionCreateActionFactory createActionactory;
			ActionDestroyActionFactory destroyActionFactory;

			const char* xmlGrammar = "Resources/TotalACtionXML.xml";
			
			NoobEngine::Parsers::WorldSharedData worldSharedData;
			NoobEngine::Parsers::WorldParseHelper worldParseHelper;
			NoobEngine::Parsers::ActionParseHelper actionParseHelper;

			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);
			parser.AddHelper(actionParseHelper);

			parser.ParseFromFile(xmlGrammar);

			World* world = reinterpret_cast<World*>(&worldSharedData.GetRootNode());
			
			// calling update
			WorldState worldState;
			worldState.mCurrentWorld = world;

			Sector* sector = reinterpret_cast<Sector*>((*world)[NoobEngine::GamePlay::Sector::sSectorsKey].Get<NoobEngine::Runtime::Scope*>());
			Entity* player = reinterpret_cast<Entity*>((*sector)[NoobEngine::GamePlay::Entity::sEntitiesKey].Get<NoobEngine::Runtime::Scope*>());

			int32_t lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(3, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(2, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(1, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(0, lifeCount);


			delete &worldSharedData.GetRootNode();
		}

		TEST_METHOD(CreateDestroyAction)
		{
			EntityFactory factory;
			ActionListIfFactory ifFactory;
			ActionPlayerAliveFactory aliveFactory;
			ActionPlayerDeadFactory deadFactory;
			ActionDecrementFactory decrementFactory;
			ActionTestFactory actiontestFactory;
			ActionCreateActionFactory createActionactory;
			ActionDestroyActionFactory destroyActionFactory;
			
			const char* xmlGrammar = "Resources/ActionCreateDestroyXml.xml";
			xmlGrammar;
			NoobEngine::Parsers::WorldSharedData worldSharedData;
			NoobEngine::Parsers::WorldParseHelper worldParseHelper;
			NoobEngine::Parsers::ActionParseHelper actionParseHelper;

			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);
			parser.AddHelper(actionParseHelper);

			parser.ParseFromFile(xmlGrammar);

			World* world = reinterpret_cast<World*>(&worldSharedData.GetRootNode());
			Sector* sector = reinterpret_cast<Sector*>((*world)[NoobEngine::GamePlay::Sector::sSectorsKey].Get<NoobEngine::Runtime::Scope*>());
			Entity* player = reinterpret_cast<Entity*>((*sector)[NoobEngine::GamePlay::Entity::sEntitiesKey].Get<NoobEngine::Runtime::Scope*>());

			int32_t lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(3, lifeCount);

			// calling update
			WorldState worldState;

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(2, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(1, lifeCount);

			world->Update(worldState);
			lifeCount = (*player)["LifeCount"].Get<int32_t>();
			Assert::AreEqual(0, lifeCount);

			delete &worldSharedData.GetRootNode();
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState ActionTests::sStartMemState;
}
