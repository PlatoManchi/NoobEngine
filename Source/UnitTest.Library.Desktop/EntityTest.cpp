#include "pch.h"
#include "CppUnitTest.h"
#include "GamePlay/Entity.h"
#include "GamePlay/Sector.h"
#include "GamePlay/World.h"
#include "Generic/Factory.h"
#include "Runtime/Scope.h"
#include "SupportingClasses/ProductFoo.h"
#include "SupportingClasses/FooEntity.h"

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
	private:
		static _CrtMemState sStartMemState;
	};

	_CrtMemState EntityTest::sStartMemState;
}