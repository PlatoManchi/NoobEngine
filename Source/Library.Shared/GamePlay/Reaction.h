#pragma once

#include "ActionList.h"
#include "Events/EventSubscriber.h"
#include "Events/EventPublisher.h"
#include "Events/Event.h"
#include "Events/EventMessageAttributed.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		class Reaction abstract : public ActionList, public Events::EventSubscriber
		{
			RTTI_DECLARATIONS(Reaction, ActionList)
		public:
			/**
				@brief Default constructor.
			*/
			Reaction();

			/**
				@brief Called every frame.
				@param[in] pWorldState Reference to the world state of current game.
			*/
			virtual void Update(WorldState& pWorldState) override;

			/**
				@brief Called when the event is fires.
			*/
			virtual void Notify(Events::EventPublisher& pPublisher) override;

		protected:
			/**
				@brief Populate prescribed attributed.
			*/
			void Populate();
		};
	}
}

// Macro
#define ConcreteReactionFactory(ConcreteReactionT)											\
class ConcreteReactionT ## Factory : public NoobEngine::Generic::Factory<Reaction>			\
{																							\
public:																						\
	ConcreteReactionT ## Factory() { Add(*this); }											\
	~ConcreteReactionT ## Factory() { Remove(ClassName()); }								\
	virtual std::string ClassName() const override {  return # ConcreteReactionT;  }		\
	virtual Reaction* Create() const override												\
	{																						\
		shared_ptr<Reaction> product = make_shared<ConcreteReactionT>();					\
		Events::Event<Events::EventMessageAttributed>::Subscribe(product);					\
		return &*product;																	\
	}																						\
};																							\
// end of macro