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

* 초기(Primary) 게임(Game) 모듈(Module) 시행(Implement)
* (ModuleImplClass, ModuleName, GameClass )
*/
IMPLEMENT_PRIMARY_GAME_MODULE(FPFModule, PF, "PF" );
