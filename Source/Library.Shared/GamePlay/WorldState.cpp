#include "pch.h"
#include "WorldState.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		WorldState::WorldState() :
			mGameTime(), mGameClock()
		{
		}

		WorldState::~WorldState()
		{
		}

		void WorldState::Update()
		{
			mGameClock.UpdateGameTime(mGameTime);
		}
	}
}