﻿#pragma once

using namespace System;
using namespace TrueGearSDK;
using namespace TrueGear;

namespace TrueGearSDKCPP {
    public ref class CppCliWrapper
    {
    private:
        TrueGearPlayer^ _player;

    public:
        CppCliWrapper();

        void CallStartMethod();
        void CallSendPlayMethod(System::String^ event);
        void CallSendPlayNoRegisteredMethod(System::String^ event);
        void CallSetupRegisterMethod(System::String^ effectUUID, System::String^ jsonStr);
    };
}