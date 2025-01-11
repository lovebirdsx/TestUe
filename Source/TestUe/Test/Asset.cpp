#include "MyObject.h"
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
	TestEqual("Path is equal", Path.ToString(), "/Game/MyTest/BP_MyObject1.BP_MyObject1_C");	

	AssetManager->LoadPrimaryAsset(PrimaryAssetId, {}, FStreamableDelegate::CreateLambda([this, AssetManager, PrimaryAssetId]()
	{
		UObject* Asset1 = AssetManager->GetPrimaryAssetObject(PrimaryAssetId);
		TestNotNull("LoadPrimaryAsset", Asset1);
		UBlueprintGeneratedClass* BlueprintClass = Cast<UBlueprintGeneratedClass>(Asset1);
		const UMyObject* MyObjectInstance = NewObject<UMyObject>(GetTransientPackage(), BlueprintClass);
		TestNotNull("NewObject", MyObjectInstance);
		TestEqual("MyObjectInstance Player Health is 101", MyObjectInstance->PlayerHealth, 101);
		
		// BP_MyObject1 引用了 BP_MyObject2, 所以 BP_MyObject2 也会被加载
		const FPrimaryAssetId PrimaryAssetId2 = FPrimaryAssetId("MyObject", "BP_MyObject2");
		TestNotNull("LoadPrimaryAsset2", AssetManager->GetPrimaryAssetObject(PrimaryAssetId2));

		AssetManager->UnloadPrimaryAsset(PrimaryAssetId);		
	}));	
	
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_AssetRegistry, "TestUe.Asset.AssetRegistry", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestAsset_AssetRegistry::RunTest(const FString& Parameters)
{
	const IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();
	FARFilter Filter;
	Filter.ClassPaths.Add(UMyObject::StaticClass()->GetClassPathName());
	Filter.bRecursiveClasses = true;

	TArray<FAssetData> AssetDataList;
	AssetRegistry.GetAssets(Filter, AssetDataList);
	TestEqual("AssetDataList.Num()", AssetDataList.Num(), 0);	
	
	const FAssetData AssetData = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath(FName("/Game/MyTest/BP_MyObject1.BP_MyObject1")));
	TestTrue("AssetData.IsValid()", AssetData.IsValid());
	TestEqual("AssetData.AssetName", AssetData.AssetName.ToString(), TEXT("BP_MyObject1"));
	TestEqual("AssetData.PackageName", AssetData.PackageName.ToString(), TEXT("/Game/MyTest/BP_MyObject1"));
	TestEqual("AssetData.AssetClass", AssetData.AssetClassPath.ToString(), TEXT("/Script/Engine.Blueprint"));

	const UObject* Asset = AssetData.GetAsset();
	TestNotNull("AssetData.GetAsset()", Asset);
	const UBlueprint* Blueprint = Cast<UBlueprint>(Asset);
	TestNotNull("Cast<UBlueprintGeneratedClass>", Blueprint);
	const UMyObject* Cdo = Blueprint->GeneratedClass->GetDefaultObject<UMyObject>();
	TestNotNull("GeneratedClass->GetDefault", Cdo);

	TestEqual("Cdo->PlayerHealth", Cdo->PlayerHealth, 101);
	
	return true;
}
