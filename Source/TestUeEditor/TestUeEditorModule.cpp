#include "TestUeEditorModule.h"
#include "Common/TestUeSettings.h"

#include "ILiveCodingModule.h"
#include "BlueprintLib/MyBPLib.h"
#include "Modules/ModuleManager.h"

IMPLEMENT_PRIMARY_GAME_MODULE(FTestUeEditor, TestUeEditor, "TestUe");

void FTestUeEditor::StartupModule()
{
	if (FModuleManager::Get().IsModuleLoaded("LiveCoding"))
	{
		ILiveCodingModule& LiveCoding = FModuleManager::LoadModuleChecked<ILiveCodingModule>("LiveCoding");
		LiveCoding.GetOnPatchCompleteDelegate().AddRaw(this, &FTestUeEditor::OnLiveCodingComplete);
	}
	
	FEditorDelegates::OnEditorInitialized.AddRaw(this, &FTestUeEditor::OnEditorInitialized);

	// 只在编辑器环境下才执行，cook时如果执行会导致editor crash，因为ShowSessionFrontend会调用到Slate相关的代码
	// 而cook环境中是没有Slate的
	if (GEditor)
	{
		// 尝试打开session frontend，方便进行自动化测试
		UMyBPLib::ShowSessionFrontend();
	}

}

void FTestUeEditor::ShutdownModule()
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

void FTestUeEditor::OnLiveCodingComplete()
{
	UMyBPLib::StartTestByPrefix(TEXT("TestUe."));	
}

void FTestUeEditor::OnBlueprintReinstanced()
{
	const UTestUeSettings* Settings = GetDefault<UTestUeSettings>();
	if (Settings->bRunTestAfterBpCompile)
	{
		UMyBPLib::StartTestByPrefix(TEXT("Project.Functional"));
	}
}

void FTestUeEditor::OnEditorInitialized(double Duration)
{
	GEditor->OnBlueprintReinstanced().AddRaw(this, &FTestUeEditor::OnBlueprintReinstanced);
}
