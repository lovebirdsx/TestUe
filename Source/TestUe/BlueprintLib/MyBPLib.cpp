#include "MyBPLib.h"

#include "AutomationControllerSettings.h"
#include "AutomationGroupFilter.h"
#include "IAutomationControllerModule.h"
#include "ILiveCodingModule.h"
#include "MyEventManager.h"

FString UMyBPLib::GetPackageName(UObject* Object)
{
	return Object->GetOutermost()->GetName();
}

void UMyBPLib::StartAutomationTest()
{	
	const IAutomationControllerManagerRef AutomationController = FModuleManager::LoadModuleChecked<IAutomationControllerModule>("AutomationController").GetAutomationController();

	AutomationController->Startup();

	// 测试以TestUe.开头的测试用例
	const TSharedPtr<AutomationFilterCollection> AutomationFilters = MakeShareable(new AutomationFilterCollection());
	const TSharedPtr<FAutomationGroupFilter> FilterAny = MakeShareable(new FAutomationGroupFilter());
	TArray<FAutomatedTestFilter> FiltersList;
	FiltersList.Add(FAutomatedTestFilter(TEXT("TestUe."), true));
	FilterAny->SetFilters(FiltersList);
	
	AutomationFilters->Add(FilterAny);
	TArray<FString> FilteredTestNames;
	AutomationController->SetFilter(AutomationFilters);
	AutomationController->GetFilteredTestNames(FilteredTestNames);
	AutomationController->SetEnabledTests(FilteredTestNames);

	UE_LOG(LogTemp, Warning, TEXT("========= Test Count = %d ========="), AutomationController->GetEnabledTestsNum());
	
	AutomationController->RunTests(true); 
}

void UMyBPLib::StartLiveCodingCompile()
{
	if (FModuleManager::Get().IsModuleLoaded("LiveCoding"))
	{
		ILiveCodingModule& LiveCoding = FModuleManager::LoadModuleChecked<ILiveCodingModule>("LiveCoding");
		LiveCoding.Compile(ELiveCodingCompileFlags::WaitForCompletion, nullptr);
	}
}

UMyEventManager* UMyBPLib::GetEventManager()
{
	return UMyEventManager::GetInstance();
}
