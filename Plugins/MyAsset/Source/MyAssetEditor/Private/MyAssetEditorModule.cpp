#include "MyAssetEditorModule.h"

#include "MyCustomAsset.h"
#include "MyCustomAssetDetails.h"

#define LOCTEXT_NAMESPACE "FMyAssetEditorModule"

void FMyAssetEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UMyCustomAsset::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FMyCustomAssetDetails::MakeInstance));
}

void FMyAssetEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(UMyCustomAsset::StaticClass()->GetFName());
	}	
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMyAssetEditorModule, MyAssetEditor)