#include "TestUe.h"

#include "ILiveCodingModule.h"
#include "BlueprintLib/MyBPLib.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FTestUe, TestUe, "TestUe");

void FTestUe::StartupModule()
{
	if (FModuleManager::Get().IsModuleLoaded("LiveCoding"))
	{
		ILiveCodingModule& LiveCoding = FModuleManager::LoadModuleChecked<ILiveCodingModule>("LiveCoding");
		LiveCoding.GetOnPatchCompleteDelegate().AddRaw(this, &FTestUe::OnLiveCodingComplete);
	}

	// 尝试打开session frontend，方便进行自动化测试
	UMyBPLib::ShowSessionFrontend();
	UMyBPLib::StartAutomationTest();
}

void FTestUe::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("LiveCoding"))
	{
		ILiveCodingModule& LiveCoding = FModuleManager::LoadModuleChecked<ILiveCodingModule>("LiveCoding");
		LiveCoding.GetOnPatchCompleteDelegate().RemoveAll(this);
	}
}

void FTestUe::OnLiveCodingComplete()
{
	UMyBPLib::StartAutomationTest();	
}
