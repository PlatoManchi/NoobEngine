#include "pch.h"
#include "ActionDecrement.h"
#include "World.h"

namespace NoobEngine
{
	namespace GamePlay
	{
		RTTI_DEFINITIONS(ActionDecrement)

		ActionDecrement::ActionDecrement() :
			Action(), mValueDatum(nullptr)
		{
			Populate();
		}

		ActionDecrement::~ActionDecrement()
		{

		}

		void ActionDecrement::Update(NoobEngine::GamePlay::WorldState& pWorldState)
		{
			pWorldState;

			if (!mValueDatum)
			{
				//mValueDatum = Search(mValueKey);
				//std::string valueKey = Append("value").Get<std::string>();
				mValueDatum = pWorldState.mCurrentWorld->ResolveDatum(mValueKey);
				if (!mValueDatum)
				{
					std::string valueKey = Append("value").Get<std::string>();
					mValueDatum = pWorldState.mCurrentWorld->ResolveDatum(valueKey);
				}
			}

			if (mValueDatum)
			{
				assert(mValueDatum->Type() == Runtime::DatumType::INTEGER);

				*mValueDatum = mValueDatum->Get<int>() - 1;
			}
		}

		void ActionDecrement::Populate()
		{
			Action::Populate();
		}
	}
}