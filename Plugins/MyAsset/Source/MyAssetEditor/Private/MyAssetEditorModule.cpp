#include "MyAssetEditorModule.h"

#include "MyCustomAsset.h"
#include "MyCustomAssetDetails.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FMyAssetEditorModule"

void FMyAssetEditorModule::StartupModule()
{
	FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyModule.RegisterCustomClassLayout(UMyCustomAsset::StaticClass()->GetFName(), FOnGetDetailCustomizationInstance::CreateStatic(&FMyCustomAssetDetails::MakeInstance));

	StyleSet = MakeShareable(new FSlateStyleSet(TEXT("MyAssetEditorStyle")));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("MyAsset")->GetBaseDir() / TEXT("Resources"));

	FSlateImageBrush *ThumbnailBrush2 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("pink-star"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *IconBrush2 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("yellow-star"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *ThumbnailBrush3 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("blue-star"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *IconBrush3 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("gray-star"), TEXT(".png")), FVector2D(128, 128));
	StyleSet->Set(TEXT("ClassThumbnail.MyCustomAsset2"), ThumbnailBrush2);
	StyleSet->Set(TEXT("ClassIcon.MyCustomAsset2"), IconBrush2);
	StyleSet->Set(TEXT("ClassThumbnail.MyCustomAsset3"), ThumbnailBrush3);
	StyleSet->Set(TEXT("ClassIcon.MyCustomAsset3"), IconBrush3);

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FMyAssetEditorModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("PropertyEditor"))
	{
		FPropertyEditorModule& PropertyModule = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");
		PropertyModule.UnregisterCustomClassLayout(UMyCustomAsset::StaticClass()->GetFName());
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FMyAssetEditorModule, MyAssetEditor)