#include "pch.h"
#include "CppUnitTest.h"
#include "GamePlay/Entity.h"
#include "GamePlay/Sector.h"
#include "GamePlay/World.h"
#include "Generic/Factory.h"
#include "Runtime/Scope.h"
#include "SupportingClasses/ProductFoo.h"
#include "SupportingClasses/FooEntity.h"

#include "Parsers/WorldSharedData.h"
#include "Parsers/WorldParseHelper.h"
#include "Parsers/XmlParseMaster.h"
#include "GamePlay/WorldState.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace NoobEngine::GamePlay;
using namespace NoobEngine::Generic;
using namespace NoobEngine::Runtime;
using namespace SupportingClasses;

namespace UnitTestLibraryDesktop
{		
	TEST_CLASS(EntityTest)
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
		
		TEST_METHOD(EntityClassTest)
		{
			// initial values
			EntityFactory factory;
			std::string entityName = "Plato";

			// testing
			Entity* newEntity = Factory<Entity>::Create("Entity");
			
			// checking if the entity is created through factory pattern
			Assert::IsTrue(nullptr != newEntity);

			Assert::AreEqual(std::string(""), newEntity->Name());
			Assert::AreEqual(std::string(""), (*newEntity)["name"].Get<std::string>());

			newEntity->SetName(entityName);

			Assert::AreEqual(entityName, newEntity->Name());
			Assert::AreEqual(entityName, (*newEntity)["name"].Get<std::string>());

			// RTTI testing
			Assert::IsTrue(newEntity->Is(Entity::TypeName()));
			Assert::IsTrue(newEntity->Is(Scope::TypeName()));
			Assert::IsFalse(newEntity->Is(ProductFoo::TypeName()));
			Assert::IsFalse(newEntity->Is("ErrorClassName"));

			Assert::IsTrue(newEntity->Is(Entity::TypeIdClass()));
			Assert::IsTrue(newEntity->Is(Scope::TypeIdClass()));
			Assert::IsFalse(newEntity->Is(ProductFoo::TypeIdClass()));

			Scope* entityAsScope = newEntity->As<Scope>();
			Assert::IsTrue(nullptr != entityAsScope);

			ProductFoo* entityAsProductFoo = newEntity->As<ProductFoo>();
			Assert::IsTrue(nullptr == entityAsProductFoo);

			delete newEntity;
		}

		TEST_METHOD(SectorClassTest)
		{
			// initial values
			EntityFactory factory;
			FooEntityFactory fooFactory;
			std::string entityName = "Plato";
			std::string sectorName = "Sector1";

			Sector newSector;

			Assert::AreEqual(std::string(""), newSector.Name());
			Assert::AreEqual(std::string(""), newSector["name"].Get<std::string>());

			newSector.SetName(sectorName);

			Assert::AreEqual(sectorName, newSector.Name());
			Assert::AreEqual(sectorName, newSector["name"].Get<std::string>());

			Datum& entities = newSector.Entities();

			Assert::AreEqual(0U, entities.Size());
			Assert::IsTrue(DatumType::TABLE == entities.Type());

			Entity& newEntity = newSector.CreateEntity("Entity", "Plato");

			entities = newSector.Entities();
			Assert::AreEqual(1U, entities.Size());

			Entity& newFooEntity = newSector.CreateEntity("FooEntity", "FooPlato");

			entities = newSector.Entities();
			Assert::AreEqual(2U, entities.Size());

			Assert::IsTrue(&newSector == &newEntity.GetParentSector());
			Assert::IsTrue(&newSector == &newFooEntity.GetParentSector());

			Assert::AreEqual(std::string("Plato"), (*entities.Get<Scope*>(0))["name"].Get<std::string>());
			Assert::AreEqual(std::string("FooPlato"), (*entities.Get<Scope*>(1))["name"].Get<std::string>());

			// RTTI test
			Assert::IsTrue(newEntity.Is(Entity::TypeName()));
			Assert::IsTrue(newEntity.Is(Scope::TypeName()));
			Assert::IsFalse(newEntity.Is(ProductFoo::TypeName()));
			Assert::IsFalse(newEntity.Is("ErrorClassName"));

			Assert::IsTrue(newEntity.Is(Entity::TypeIdClass()));
			Assert::IsTrue(newEntity.Is(Scope::TypeIdClass()));
			Assert::IsFalse(newEntity.Is(ProductFoo::TypeIdClass()));

			Scope* entityAsScope = newEntity.As<Scope>();
			Assert::IsTrue(nullptr != entityAsScope);

			ProductFoo* entityAsProductFoo = newEntity.As<ProductFoo>();
			Assert::IsTrue(nullptr == entityAsProductFoo);

			Assert::IsTrue(newFooEntity.Is(Entity::TypeName()));
			Assert::IsTrue(newFooEntity.Is(Scope::TypeName()));
			Assert::IsFalse(newFooEntity.Is(ProductFoo::TypeName()));
			Assert::IsFalse(newFooEntity.Is("ErrorClassName"));

			Assert::IsTrue(newFooEntity.Is(Entity::TypeIdClass()));
			Assert::IsTrue(newFooEntity.Is(Scope::TypeIdClass()));
			Assert::IsFalse(newFooEntity.Is(ProductFoo::TypeIdClass()));

			entityAsScope = newFooEntity.As<Scope>();
			Assert::IsTrue(nullptr != entityAsScope);

			entityAsProductFoo = newFooEntity.As<ProductFoo>();
			Assert::IsTrue(nullptr == entityAsProductFoo);
		}

		TEST_METHOD(WorldClassTest)
		{
			// initial values
			EntityFactory factory;
			FooEntityFactory fooFactory;
			std::string entityName = "Plato";
			std::string sectorName = "Sector1";
			std::string worldName = "PlatoWorld";

			// testing
			World newWorld;

			Assert::AreEqual(std::string(""), newWorld.Name());
			Assert::AreEqual(std::string(""), newWorld["name"].Get<std::string>());

			newWorld.SetName(worldName);

			Assert::AreEqual(worldName, newWorld.Name());
			Assert::AreEqual(worldName, newWorld["name"].Get<std::string>());

			Datum& sectors = newWorld.Sectors();

			Assert::AreEqual(0U, sectors.Size());
			Assert::IsTrue(DatumType::TABLE == sectors.Type());

			Sector& newSector = newWorld.CreateSector(sectorName);
			sectors = newWorld.Sectors();

			Assert::AreEqual(1U, sectors.Size());
			Assert::IsTrue(&newWorld == &newSector.GetParentWorld());
			Assert::AreEqual(sectorName, (*sectors.Get<Scope*>(0))["name"].Get<std::string>());


			Datum& entities = newSector.Entities();

			Assert::AreEqual(0U, entities.Size());
			Assert::IsTrue(DatumType::TABLE == entities.Type());

			Entity& newEntity = newSector.CreateEntity("Entity", "Plato");

			entities = newSector.Entities();
			Assert::AreEqual(1U, entities.Size());

			Entity& newFooEntity = newSector.CreateEntity("FooEntity", "FooPlato");

			entities = newSector.Entities();
			Assert::AreEqual(2U, entities.Size());

			Assert::IsTrue(&newSector == &newEntity.GetParentSector());
			Assert::IsTrue(&newSector == &newFooEntity.GetParentSector());

			Assert::AreEqual(std::string("Plato"), (*entities.Get<Scope*>(0))["name"].Get<std::string>());
		}

		TEST_METHOD(WorldGrammarXMLParseTest)
		{
			EntityFactory factory;
			FooEntityFactory fooFactory;

			const char* xmlGrammar = "Resources/WorldXmlGrammar.xml";

			NoobEngine::Parsers::WorldSharedData worldSharedData;
			NoobEngine::Parsers::WorldParseHelper worldParseHelper;

			// parser
			NoobEngine::Parsers::XmlParseMaster parser;
			parser.SetSharedData(worldSharedData);
			parser.AddHelper(worldParseHelper);

			parser.ParseFromFile(xmlGrammar);

			// check if parsing happened properly
			Assert::IsTrue(&worldSharedData.GetRootNode() == &worldSharedData.GetCurrentNode());

			World* world = reinterpret_cast<World*>(&worldSharedData.GetRootNode());

			Scope* settingsScope = (*world)["Settings"].Get<Scope*>();

			Assert::AreEqual(1920.0f, (*settingsScope)["ResolutionX"].Get<float>());
			Assert::AreEqual(1080.0f, (*settingsScope)["ResolutionY"].Get<float>());

			Datum& sectors = world->Sectors();
			Sector* sector1 = reinterpret_cast<Sector*>(sectors.Get<Scope*>());

			Assert::AreEqual(1U, sectors.Size());
			Assert::AreEqual(std::string("Sector1"), (*sector1)["key"].Get<std::string>() );
			Assert::AreEqual(50, (*sector1)["TotalEnemyCount"].Get<int>());
			
			Datum& entities = sector1->Entities();

			Assert::AreEqual(2U, entities.Size());
			
			Entity* player = reinterpret_cast<Entity*>(entities.Get<Scope*>(0));
			Assert::AreEqual(std::string("Player"), (*player)["key"].Get<std::string>());
			Assert::AreEqual(std::string("Plato"), (*player)["Name"].Get<std::string>());
			Assert::AreEqual(3, (*player)["Life"].Get<int>());
			Assert::AreEqual(100.0f, (*player)["Health"].Get<float>());
			Assert::IsTrue(glm::vec4() == (*player)["Pos"].Get<glm::vec4>());
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == (*player)["Transform"].Get<glm::mat4x4>());

			Assert::AreEqual(1, (*player)["ArrayInt"].Get<int>(0));
			Assert::AreEqual(2, (*player)["ArrayInt"].Get<int>(1));
			Assert::AreEqual(3, (*player)["ArrayInt"].Get<int>(2));

			Assert::AreEqual(1.0f, (*player)["ArrayFloat"].Get<float>(0));
			Assert::AreEqual(2.0f, (*player)["ArrayFloat"].Get<float>(1));
			Assert::AreEqual(3.0f, (*player)["ArrayFloat"].Get<float>(2));

			Assert::AreEqual(std::string("String1"), (*player)["ArrayString"].Get<std::string>(0));
			Assert::AreEqual(std::string("String2"), (*player)["ArrayString"].Get<std::string>(1));
			Assert::AreEqual(std::string("String3"), (*player)["ArrayString"].Get<std::string>(2));

			Assert::IsTrue(glm::vec4(0, 0, 0, 0) == (*player)["ArrayVec4"].Get<glm::vec4>(0));
			Assert::IsTrue(glm::vec4(1, 2, 3, 4) == (*player)["ArrayVec4"].Get<glm::vec4>(1));
			Assert::IsTrue(glm::vec4(5, 6, 7, 8) == (*player)["ArrayVec4"].Get<glm::vec4>(2));

			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0) == (*player)["ArrayMat4x4"].Get<glm::mat4x4>(0));
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0) == (*player)["ArrayMat4x4"].Get<glm::mat4x4>(1));
			Assert::IsTrue(glm::mat4x4(0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 4, 0, 0, 0, 0) == (*player)["ArrayMat4x4"].Get<glm::mat4x4>(2));

			// testing for foo entity
			Entity* fooEntity = reinterpret_cast<Entity*>(entities.Get<Scope*>(1));
			Assert::IsTrue(fooEntity->Is(FooEntity::TypeIdClass()));

			Assert::AreEqual(3, (*fooEntity)["Life"].Get<int>());

			// calling update
			WorldState worldState;
			world->Update(worldState);

			Assert::AreEqual(4, (*fooEntity)["Life"].Get<int>());

			delete &worldSharedData.GetRootNode();
		}
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityTest::sStartMemState;
}