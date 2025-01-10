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
	
	FEditorDelegates::OnEditorInitialized.AddRaw(this, &FTestUe::OnEditorInitialized);

	// 尝试打开session frontend，方便进行自动化测试
	UMyBPLib::ShowSessionFrontend();	
}

void FTestUe::ShutdownModule()
{
	if (GEditor)
	{
		GEditor->OnBlueprintReinstanced().RemoveAll(this);
	}

	FEditorDelegates::OnEditorInitialized.RemoveAll(this);
	
	if (FModuleManager::Get().IsModuleLoaded("LiveCoding"))
	{
		ILiveCodingModule& LiveCoding = FModuleManager::LoadModuleChecked<ILiveCodingModule>("LiveCoding");
		LiveCoding.GetOnPatchCompleteDelegate().RemoveAll(this);
	}
}

void FTestUe::OnLiveCodingComplete()
{
	UMyBPLib::StartTestByPrefix(TEXT("TestUe."));	
}

void FTestUe::OnBlueprintReinstanced()
{
	UMyBPLib::StartTestByPrefix(TEXT("Project.Functional"));
}

void FTestUe::OnEditorInitialized(double Duration)
{
	GEditor->OnBlueprintReinstanced().AddRaw(this, &FTestUe::OnBlueprintReinstanced);
}
