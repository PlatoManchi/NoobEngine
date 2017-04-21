#pragma once
#include "Runtime/RTTI.h"
#include "GamePlay/GameTime.h"
#include "EventPublisher.h"
#include "Container/Vector.h"

namespace NoobEngine
{
	namespace Events
	{
		class EventQueue : public Runtime::RTTI
		{
			RTTI_DECLARATIONS(EventQueue, RTTI)

		public:
			/**
				@brief Default constructor.
			*/
			EventQueue();

			/**
				Remove copy semantics to make EventQueue thread safe
			*/
			EventQueue(const EventQueue& pOther) = delete;
			EventQueue& operator=(const EventQueue& pOther) = delete;

			/**
				@brief Push the event publisher into the list of publishers and save the enqueued time and delay.
				@details The delay time is in seconds
				@param[in] pEventPublisher Shared pointer to the event publisher.
				@param[in] pGameTime Reference to the game time object that holds the current time.
				@param[in] pDelay float that denotes the amount of time in seconds the event should be delayed before it notifies.
			*/
			void Enqueue(std::shared_ptr<EventPublisher> pEventPublisher, const GamePlay::GameTime& pGameTime, float pDelay = 0.0f);

			/**
				@brief Fire the event immediately without waiting for the expiration.
				@param[in] pEventPublisher The event publisher which should to notified.
			*/
			void Send(std::shared_ptr<EventPublisher> pEventPublisher);

			/**
				@brief called every frame
				param[in] pGameTime The game time object that holds the clock details.
			*/
			void Update(const GamePlay::GameTime& pGameTime);

			/**
				@brief Remove all the publishers from queue.
			*/
			void Clear();

			/**
				@brief Return true if the publisher list is empty.
				@return boolean that holds if the publisher list is empty or not.
			*/
			bool IsEmpty();

			/**
				@brief Return the number of publishers queued in the queue.
				@return unsigned int.
			*/
			uint32_t Size();

		protected:
			/**
				Struct that holds the publisher information.
			*/
			struct Publisher
			{
				std::shared_ptr<EventPublisher> mPublisher;
				std::chrono::high_resolution_clock::time_point mEnqueuedTime;
				std::chrono::system_clock::duration mDelay;
			};

			/**
				List that holds all the publishers.
			*/
			Container::Vector<Publisher> mPublisherList;

			/**
				Mutex used for making EventQueue thread safe
			*/
			std::mutex mMutex;
		};
	}
}