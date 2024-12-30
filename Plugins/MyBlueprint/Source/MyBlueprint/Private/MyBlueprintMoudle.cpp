// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBlueprintMoudle.h"

#include "AssetToolsModule.h"
#include "FAssetTypeActions_MyBlueprint.h"
#include "IAssetTools.h"
#include "MyBlueprintFactory.h"
#include "Factories/BlueprintFactory.h"

#define LOCTEXT_NAMESPACE "FMyBlueprintModule"

void FMyBlueprintModule::StartupModule()
{
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	const TSharedPtr<FAssetTypeActions_MyBlueprint> MyFactoryActions = MakeShareable(new FAssetTypeActions_MyBlueprint());
	AssetTools.RegisterAssetTypeActions(MyFactoryActions.ToSharedRef());

	CreatedAssetTypeActions.Add(MyFactoryActions);
}

void FMyBlueprintModule::ShutdownModule()
{
	if (FModuleManager::Get().IsModuleLoaded("AssetTools"))
	{
		IAssetTools& AssetTools = FModuleManager::GetModuleChecked<FAssetToolsModule>("AssetTools").Get();

		for (TSharedPtr MyFactoryActions : CreatedAssetTypeActions)
		{
			AssetTools.UnregisterAssetTypeActions(MyFactoryActions.ToSharedRef());
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyBlueprintModule, MyBlueprint)