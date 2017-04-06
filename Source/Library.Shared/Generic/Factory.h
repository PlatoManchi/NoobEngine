#pragma once
#include "Container/Hashmap.h"

namespace NoobEngine
{
	namespace Generic
	{
		template<class T>
		class Factory
		{
			typedef NoobEngine::Container::Hashmap<string, Factory<T>*> FactoryMap;
		public:
			/**
				@brief Default constructor
			*/
			Factory() = default;

			/**
				@brief Default destructor
			*/
			virtual ~Factory() = default;

			/**
				@brief Given class name, returns associated concrete factory.
				@details If the name is not found then it returns nullptr.
				@param[in] pName String contains the name of the class.
				@return Pointer to the Factory.
			*/
			Factory* Find(std::string pName) const;

			/**
				@brief Given a class name, returns a new object of that type.
				@details If the name is not found then it will return nullptr.
				@param[in] pName String contains the name of the class.
				@return Pointer to the object.
			*/
			static T* Create(std::string pTypeName);

			/**
				@brief Return the begin iterator of the hashmap
				@return Hashmap iterator
			*/
			typename FactoryMap::Iterator begin() const;

			/**
				@brief Return the end iterator of the hashmap
				@return Hashmap iterator
			*/
			typename FactoryMap::Iterator end() const;

			/**
				@brief Add the concrete factory to the list of factories.
				@param[in] pFactory Reference to the factory
			*/
			void Add(const Factory& pFactory);

			/**
				@brief Remove the concrete factory from the list of factories.
				@param[in] pFactoryName ClassName of the factory that needs to be removed.
			*/
			void Remove(std::string pFactoryName);

			/**
				@brief Create a new object of type and return the pointer
				@details If there is no class with associated name it will return nullptr.
				@param[in] pName String that holds the ClassName.
			*/
			virtual T* Create() const = 0;

			/**
				@brief Return the name of the class.
				@details This function should be overloaded by each derived class.
				@return String Name of the class.
			*/
			virtual std::string ClassName() const = 0;
		protected:
		private:
			/**
				Contains the list of all factories created.
			*/
			static FactoryMap mFactories;
		};
	}
}
#include "Factory.inl"

// Macro
#define ConcreteFactory(AbstractProductT, ConcreteProductT)									\
class ConcreteProductT ## Factory : public NoobEngine::Generic::Factory<AbstractProductT>	\
{																							\
public:																						\
	ConcreteProductT ## Factory() { Add(*this); }											\
	~ConcreteProductT ## Factory() { Remove(ClassName()); }									\
	virtual std::string ClassName() const override {  return # ConcreteProductT;  }			\
	virtual AbstractProductT* Create() const override										\
	{																						\
		AbstractProductT* product = new ConcreteProductT();									\
		return product;																		\
	}																						\
};																							\
// end of macro