#pragma once
#include "GamePlay/GameClock.h"
#include "GamePlay/GameTime.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		/**
			Forward declaring
		*/
		class World;
		class Sector;
		class Entity;
		class Action;

		class WorldState final
		{
		public:
			/**
				@brief Default constructor.
			*/
			WorldState();

			/**
				@brief Default destructor.
			*/
			~WorldState();

			/**
				Update the time states
			*/
			void Update();

			/**
				Pointer to current world that is being processed.
			*/
			World* mCurrentWorld;

			/**
				Pointer to current sector that is being processed.
			*/
			Sector* mCurrentSector;

			/**
				Pointer to current entity that is being processed.
			*/
			Entity* mCurrentEntity;

			/**
				Pointer to current action that is being processed.
			*/
			Action* mCurrentAction;

			/**
				The timer that calculate time elapsed and time since game started.
			*/
			GameTime mGameTime;
		private:
			/**
				The game clock used by world state to keep track of time.
			*/
			GameClock mGameClock;

		};
	}
}