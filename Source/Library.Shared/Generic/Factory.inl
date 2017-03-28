#include "pch.h"
#include "Factory.h"

namespace NoobEngine
{
	namespace Generic
	{
		template<class T>
		Container::Hashmap<string, Factory<T>*> Factory<T>::mFactories;

		template<class T>
		Factory<T>* Factory<T>::Find(std::string pName) const
		{
			if (mFactories.ContainsKey(pName))
			{
				return mFactories[pName];
			}
			return nullptr;
		}

		template<class T>
		T* Factory<T>::Create(std::string pName)
		{
			if (mFactories.ContainsKey(pName))
			{
				return mFactories[pName]->Create();
			}
			return nullptr;
		}

		template<class T>
		typename Factory<T>::FactoryMap::Iterator Factory<T>::begin() const
		{
			return mFactories.begin();
		}

		template<class T>
		typename Factory<T>::FactoryMap::Iterator Factory<T>::end() const
		{
			return mFactories.end();
		}

		template<class T>
		void Factory<T>::Add(const Factory<T>& pFactory)
		{
			std::string name = pFactory.ClassName();
			mFactories[pFactory.ClassName()] = const_cast<Factory<T>*>(&pFactory);
		}

		template<class T>
		void Factory<T>::Remove(std::string pFactoryName)
		{
			mFactories.Remove(pFactoryName);
		}
	}
}