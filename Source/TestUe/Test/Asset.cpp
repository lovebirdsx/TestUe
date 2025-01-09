#include "Engine/AssetManager.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_AssetManager, "TestUe.Asset.AssetManager", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestAsset_AssetManager::RunTest(const FString& Parameters)
{	
	UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
	TestNotNull("AssetManager", AssetManager);

	const FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId("MyObject", "BP_MyObject1");	
	const FSoftObjectPath Path = AssetManager->GetPrimaryAssetPath(PrimaryAssetId);
	TestTrue("Path.IsValid()", Path.IsValid());

	AssetManager->LoadPrimaryAsset(PrimaryAssetId, {}, FStreamableDelegate::CreateLambda([this, AssetManager, PrimaryAssetId]()
	{
		TestNotNull("LoadPrimaryAsset", AssetManager->GetPrimaryAssetObject(PrimaryAssetId));
	}));	
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_AssetRegistry, "TestUe.Asset.AssetRegistry", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestAsset_AssetRegistry::RunTest(const FString& Parameters)
{	
	return true;
}
