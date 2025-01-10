#include "MyBPLib.h"

#include "AutomationControllerSettings.h"
#include "AutomationGroupFilter.h"
#include "IAutomationControllerModule.h"
#include "ILiveCodingModule.h"
#include "ISessionFrontendModule.h"
#include "MyEventManager.h"
#include "PackageTools.h"
#include "Selection.h"

FString UMyBPLib::GetPackageName(UObject* Object)
{
	return Object->GetOutermost()->GetName();
}

void UMyBPLib::StartAutomationTest()
{	
	const IAutomationControllerManagerRef AutomationController = FModuleManager::LoadModuleChecked<IAutomationControllerModule>("AutomationController").GetAutomationController();
	AutomationController->RunTests(true); 
}

void UMyBPLib::StartTestUeTest()
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

void UMyBPLib::ShowSessionFrontend()
{
	if (FModuleManager::Get().IsModuleLoaded("SessionFrontend"))
	{
		ISessionFrontendModule& SessionFrontend = FModuleManager::LoadModuleChecked<ISessionFrontendModule>("SessionFrontend");
		SessionFrontend.InvokeSessionFrontend();
	}
	else
	{
		FModuleManager::Get().LoadModule("SessionFrontend", ELoadModuleFlags::LogFailures);
		ShowSessionFrontend();
	}
}

void UMyBPLib::UnloadSelectedAssets()
{
	if (!GEditor)
	{
		UE_LOG(LogTemp, Error, TEXT("GEditor is null."));
		return;
	}
	
    // 获取当前选中的资产
	USelection* Selection = GEditor->GetSelectedObjects();
	if (!Selection)
	{
		UE_LOG(LogTemp, Error, TEXT("Selection is null."));
		return;
	}
    
	TArray<UObject*> SelectedObjects;
	Selection->GetSelectedObjects<UObject>(SelectedObjects);
	if (SelectedObjects.Num() == 0)
	{
		UE_LOG(LogTemp, Display, TEXT("No asset is selected."));
		return;
	}
	
	TArray<FString> UnloadedPackageNames;
    for (const UObject* Asset : SelectedObjects)
    {
        if (!Asset || !Asset->IsAsset())
		{
			continue;
		}
     
    	UPackage* Package = Asset->GetOutermost();
    	if (!Package)
    	{
    		continue;
    	}
    	
    	UnloadedPackageNames.Add(Package->GetName());
    	UPackageTools::UnloadPackages({Package});
    }

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Join(UnloadedPackageNames, TEXT("\n"))));        
}

UMyEventManager* UMyBPLib::GetEventManager()
{
	return UMyEventManager::GetInstance();
}
