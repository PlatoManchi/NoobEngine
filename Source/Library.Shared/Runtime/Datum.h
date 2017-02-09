#pragma once
#include "pch.h"

namespace NoobEngine
{
	namespace Runtime
	{
		enum class DatumType {Interger, Float, String, Vector4, Matrix4};

		class Datum
		{
		public:

		private:
			/**
				
			*/
			union DatumValue
			{
				int32_t* mIntData;
				float* mFloatData;
				std::string* mStrData;
			};

			/**
				
			*/
			DatumType mType;

			/**
				
			*/
			DatumValue* mData;
		};
	}
}