#include "MyAssetEditorModule.h"

#include "MyCustomAsset.h"
#include "CustomEditor1/MyCustomAssetDetails.h"
#include "ResouceManager.h"
#include "CustomEditor3/SCustomGraphPin3.h"

#define LOCTEXT_NAMESPACE "FMyAssetEditorModule"

void FMyAssetEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UMyCustomAsset::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FMyCustomAssetDetails::MakeInstance));

	ResourceManager = MakeShareable(new FResourceManager);
	ResourceManager->RegisterResource();

	CustomPinFactory = MakeShareable(new FCustomPinFactory3);
	FEdGraphUtilities::RegisterVisualPinFactory(CustomPinFactory);
}

void FMyAssetEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(UMyCustomAsset::StaticClass()->GetFName());
	}

	if (ResourceManager.IsValid())
	{
		ResourceManager->UnregisterResource();
		ResourceManager.Reset();
	}

	if (CustomPinFactory.IsValid())
	{
		FEdGraphUtilities::UnregisterVisualPinFactory(CustomPinFactory);
		CustomPinFactory.Reset();
	}
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMyAssetEditorModule, MyAssetEditor)