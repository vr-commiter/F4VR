#include "f4se_common/f4se_version.h"
#include <shlobj.h>
//#include <intrin.h>
//#include <string>
//#include "f4se/PluginAPI.h"	
//#include <common/IDebugLog.h>
//#include <f4se/GameEvents.h>
#include <F4VR_TrueGear/Hook.h>


static F4SEMessagingInterface* g_messaging = NULL;
static PluginHandle g_pluginHandle = kPluginHandle_Invalid;
static F4SEPapyrusInterface* g_papyrus = NULL;
static F4SEObjectInterface* g_object = NULL;

extern "C"
{
	void OnF4SEMessage(F4SEMessagingInterface::Message* msg)
	{
		if (msg)
		{
			if (msg->type == F4SEMessagingInterface::kMessage_GameLoaded)
			{
				F4VR_TrueGear::LoadFuncs();
				_MESSAGE("Building Event Sinks...");

				F4VR_TrueGear::MenuOpenCloseHandler::Register();
				GetEventDispatcher<TESHitEvent>()->AddEventSink(&F4VR_TrueGear::g_HitEventHandler);
				GetEventDispatcher<TESEquipEvent>()->AddEventSink(&F4VR_TrueGear::g_TESEquipEventHandler);
				_MESSAGE("Building Event Sinks...Done.");
			}
		}
	}	

	

	bool F4SEPlugin_Query(const F4SEInterface* f4se, PluginInfo* info)
	{
		gLog.OpenRelative(CSIDL_MYDOCUMENTS, "\\My Games\\Fallout4VR\\F4SE\\F4VR_TrueGear.log");
		gLog.SetPrintLevel(IDebugLog::kLevel_Error);
		gLog.SetLogLevel(IDebugLog::kLevel_DebugMessage);

		std::string logMsg("F4VR_TrueGear: 1.0.0");
		_MESSAGE(logMsg.c_str());

		info->infoVersion = PluginInfo::kInfoVersion;
		info->name = "F4VR_TrueGear";
		info->version = 010101;

		g_pluginHandle = f4se->GetPluginHandle();

		std::string f4seVers = "F4SEVR Version: ";
		f4seVers += std::to_string(f4se->runtimeVersion);
		_MESSAGE(f4seVers.c_str());

		if (f4se->isEditor)
		{
			_MESSAGE("loaded in editor, marking as incompatible");

			return false;
		}
		else if (f4se->runtimeVersion < CURRENT_RELEASE_RUNTIME)
		{
			_MESSAGE("unsupported runtime version %08X", f4se->runtimeVersion);

			return false;
		}
		return true;
	}

	bool F4SEPlugin_Load(const F4SEInterface* F4SE) {
		_MESSAGE("F4SE_TrueGear is loaded");

		g_messaging = (F4SEMessagingInterface*)F4SE->QueryInterface(kInterface_Messaging);
		g_messaging->RegisterListener(g_pluginHandle, "F4SE", OnF4SEMessage);

		

		return true;
	}
}