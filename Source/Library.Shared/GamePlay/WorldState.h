#pragma once

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

		class WorldState
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
		};
	}
}