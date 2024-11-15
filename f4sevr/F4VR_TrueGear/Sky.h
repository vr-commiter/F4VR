#pragma once

#include "f4se/GameReferences.h"
#include <common/ITypes.h>
class TESWeather2;
class TESClimate;
class TESRegion;

namespace F4VR_TrueGear
{
	class Sky2
	{
	public:
		virtual ~Sky2();

		UInt64                      array[11];
	};
	class Sky
	{
	public:
		virtual ~Sky();

		UInt8                      unk0[0x40];                        // 0x18
		TESClimate* climate;                         // 0x40
		TESWeather2* outgoingWeather;                  // 0x48  current weather active or being transitioned to
		TESWeather2* currentWeather;                 // 0x50  previous weather during transition
		TESWeather2* nextWeather;                     // 0x58  next weather in queue, transition hasn't begun yet
		
	};

}
