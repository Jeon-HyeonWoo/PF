// Copyright Epic Games, Inc. All Rights Reserved.

#include "PF.h"
#include "Modules/ModuleManager.h"

class FPFModule : public FDefaultGameModuleImpl
{
	/*
	* ModuleInferface
	*/
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};

void FPFModule::StartupModule()
{


}
void FPFModule::ShutdownModule()
{

}
/*

* �ʱ�(Primary) ����(Game) ���(Module) ����(Implement)
* (ModuleImplClass, ModuleName, GameClass )
*/
IMPLEMENT_PRIMARY_GAME_MODULE(FPFModule, PF, "PF" );
