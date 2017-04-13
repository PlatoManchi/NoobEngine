
namespace NoobEngine
{
	namespace Events
	{
		template<typename T>
		RTTI_DEFINITIONS(Event<T>)


		template<typename T>
		Container::Vector<std::shared_ptr<EventSubscriber>> Event<T>::sSubscriberList;

		template<typename T>
		Event<T>::Event(T& pPayload) :
			EventPublisher(sSubscriberList), mPayload(pPayload)
		{
		}

		template<typename T>
		Event<T>::Event(Event<T>& pOther) :
			EventPublisher(pOther)
		{
			mPayload = pOther.mPayload;
		}

		template<typename T>
		typename Event<T>& Event<T>::operator=(Event<T>& pOther)
		{
			if (this != &pOther)
			{
				EventPublisher::operator=(pOther);

				mPayload = pOther.mPayload;
			}
			return *this;
		}

		template<typename T>
		Event<T>::Event(Event<T>&& pOther) :
			EventPublisher(std::move(pOther))
		{
			mPayload = std::move(pOther.mPayload);
		}

		template<typename T>
		Event<T>& Event<T>::operator=(Event<T>&& pOther)
		{
			if (this != &pOther)
			{
				EventPublisher::operator=(std::move(pOther));

				mPayload = std::move(pOther.mPayload);
			}
			return *this;
		}

		template<class T>
		void Event<T>::Subscribe(std::shared_ptr<EventSubscriber> pSubscriber)
		{
			if (pSubscriber != nullptr)
			{
				sSubscriberList.PushBack(pSubscriber);
			}
		}

		template<typename T>
		void Event<T>::Unsubscribe(std::shared_ptr<EventSubscriber> pSubscriber)
		{
			if (pSubscriber != nullptr)
			{
				sSubscriberList.Remove(pSubscriber);
			}
		}

		template<typename T>
		void Event<T>::UnsubscribeAll()
		{
			sSubscriberList.Clear();
		}

		template<typename T>
		const T& Event<T>::Message() const
		{
			return mPayload;
		}
	}
}