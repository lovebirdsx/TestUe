#include "MyBPLib.h"

#include "AutomationControllerSettings.h"
#include "AutomationGroupFilter.h"
#include "ContentBrowserModule.h"
#include "IAutomationControllerModule.h"
#include "IContentBrowserSingleton.h"
#include "ILiveCodingModule.h"
#include "ISessionFrontendModule.h"
#include "MyEventManager.h"
#include "PackageTools.h"

namespace 
{
	void GetSelectedAssets(TArray<FAssetData>& SelectedAssets)
	{		
		if (!GEditor)
		{
			UE_LOG(LogTemp, Error, TEXT("GEditor is null."));
			return;
		}

		// 获取Content Browser模块
		const FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
		IContentBrowserSingleton& ContentBrowser = ContentBrowserModule.Get();		

		// 获取选中的资产		
		ContentBrowser.GetSelectedAssets(SelectedAssets);		
	}
}

FString UMyBPLib::GetPackageName(UObject* Object)
{
	return Object->GetOutermost()->GetName();
}

void UMyBPLib::StartAutomationTest()
{	
	const IAutomationControllerManagerRef AutomationController = FModuleManager::LoadModuleChecked<IAutomationControllerModule>("AutomationController").GetAutomationController();
	AutomationController->RunTests(true); 
}

void UMyBPLib::StartTestByPrefix(const FString& Prefix)
{
	const IAutomationControllerManagerRef AutomationController = FModuleManager::LoadModuleChecked<IAutomationControllerModule>("AutomationController").GetAutomationController();

	AutomationController->Startup();

	const TSharedPtr<AutomationFilterCollection> AutomationFilters = MakeShareable(new AutomationFilterCollection());
	const TSharedPtr<FAutomationGroupFilter> FilterAny = MakeShareable(new FAutomationGroupFilter());
	TArray<FAutomatedTestFilter> FiltersList;
	FiltersList.Add(FAutomatedTestFilter(Prefix, true));
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
	TArray<FAssetData> SelectedAssets;
	GetSelectedAssets(SelectedAssets);
	if (SelectedAssets.Num() == 0)
	{		
		return;
	}
	
	TArray<FString> UnloadedPackageNames;
    for (const FAssetData Asset : SelectedAssets)
    {
        if (!Asset.IsValid())
        {
	        continue;
        }

    	const UObject* Object = Asset.FastGetAsset();
    	if (!Object)
		{
			continue;
		}
    	
    	UnloadedPackageNames.Add(Object->GetPathName());
    	UPackageTools::UnloadPackages({Object->GetPackage()});
    }

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Join(UnloadedPackageNames, TEXT("\n"))));
}

void UMyBPLib::LoadSelectedAssets()
{
	TArray<FAssetData> SelectedAssets;
	GetSelectedAssets(SelectedAssets);
	if (SelectedAssets.Num() == 0)
	{		
		return;
	}

	TArray<FString> Lines;
	for (const FAssetData Asset : SelectedAssets)
	{
		if (!Asset.IsValid())
		{
			continue;
		}

		const UObject* Object = Asset.FastGetAsset();
		if (Object)
		{
			Lines.Add(FString::Printf(TEXT("%s is already loaded."), *Object->GetPathName()));
			continue;
		}
		
		UPackageTools::LoadPackage(Asset.PackageName.ToString());
		Lines.Add(FString::Printf(TEXT("%s is loaded."), *Asset.PackageName.ToString()));
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Join(Lines, TEXT("\n"))));
}

void UMyBPLib::ShowSelectedAssetsLoadInfo()
{
	TArray<FAssetData> SelectedAssets;
	GetSelectedAssets(SelectedAssets);
	if (SelectedAssets.Num() == 0)
	{		
		FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(TEXT("No asset is selected.")));
		return;
	}

	TArray<FString> Lines;
	Lines.Add(FString::Printf(TEXT("Selected Asset Count: %d"), SelectedAssets.Num()));

	for (const FAssetData Asset : SelectedAssets)
	{
		if (!Asset.IsValid())
		{
			continue;
		}
		
		const bool bIsLoaded = Asset.FastGetAsset() != nullptr;
		
		FString Line = FString::Printf(TEXT("PackageName: %s, IsLoaded: %d"), *Asset.PackageName.ToString(), bIsLoaded);
		Lines.Add(Line);
	}

	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString(FString::Join(Lines, TEXT("\n"))));
}

UMyEventManager* UMyBPLib::GetEventManager()
{
	return UMyEventManager::GetInstance();
}
