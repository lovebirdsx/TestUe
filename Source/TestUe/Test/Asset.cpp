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
		
		// BP_MyObject1 引用了 BP_MyObject2, 所以 BP_MyObject2 也会被加载
		const FPrimaryAssetId PrimaryAssetId2 = FPrimaryAssetId("MyObject", "BP_MyObject2");
		TestNotNull("LoadPrimaryAsset2", AssetManager->GetPrimaryAssetObject(PrimaryAssetId2));
	}));	
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_AssetRegistry, "TestUe.Asset.AssetRegistry", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestAsset_AssetRegistry::RunTest(const FString& Parameters)
{	
	return true;
}
