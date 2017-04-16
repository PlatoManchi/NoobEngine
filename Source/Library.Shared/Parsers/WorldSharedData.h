#pragma once
#include "XmlSharedData.h"

namespace NoobEngine
{
	namespace Parsers
	{
		class WorldSharedData : public XmlSharedData
		{
			RTTI_DECLARATIONS(WorldSharedData, XmlSharedData)

			friend class WorldParseHelper;
			friend class ActionParseHelper;
			friend class ReactionParseHelper;
		public:
			
			/**
				@brief Default constructor
			*/
			WorldSharedData();

			/**
				@brief Default destructor
			*/
			virtual ~WorldSharedData();

			/**
				@brief Create a clone of current WorldSharedData object and return the pointer as shared data.
				@details This will create a new WorldSharedData, but the data will not reflect the cloned object.
				@return Pointer to SharedData that is a clone of this SharedData object.
			*/
			virtual SharedData* Clone() const override;
		protected:
			bool mIsActionList;
		};
	}
}