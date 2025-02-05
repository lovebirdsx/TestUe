#include "TestUe/Test/MyObject.h"
#include "PackageTools.h"
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

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_Load, "TestUe.Asset.Load", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestAsset_Load::RunTest(const FString& Parameters)
{
	const FName PackageName1 = "/Game/MyTest/BP_MyObject1";
	const FName AssetName1 = "BP_MyObject1";
	const FName PackageName2 = "/Game/MyTest/BP_MyObject2";
	const FName AssetName2 = "BP_MyObject2";
	const FName PackageName3 = "/Game/MyTest/BP_MyObject3";
	const FName AssetName3 = "BP_MyObject3";

	const IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();
	const FAssetData Asset1 = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath::ConstructFromPackageAsset(PackageName1, AssetName1));
	const FAssetData Asset2 = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath::ConstructFromPackageAsset(PackageName2, AssetName2));
	const FAssetData Asset3 = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath::ConstructFromPackageAsset(PackageName3, AssetName3));

	TestTrue("Asset1.IsValid()", Asset1.IsValid());
	TestTrue("Asset2.IsValid()", Asset2.IsValid());
	TestTrue("Asset3.IsValid()", Asset3.IsValid());	

	// 先确保资源未加载
	UPackageTools::UnloadPackages({Asset1.GetPackage(), Asset2.GetPackage(), Asset3.GetPackage()});

	TestNull("Asset1.FastGetAsset() == nullptr", Asset1.FastGetAsset());
	TestNull("Asset2.FastGetAsset() == nullptr", Asset2.FastGetAsset());
	TestNull("Asset3.FastGetAsset() == nullptr", Asset3.FastGetAsset());

	// 加载资源1
	UPackageTools::LoadPackage(PackageName1.ToString());

	// 由于资源1引用了资源2, 所以资源2也会被加载
	TestNotNull("Asset1.FastGetAsset() != nullptr", Asset1.FastGetAsset());
	TestNotNull("Asset2.FastGetAsset() != nullptr", Asset2.FastGetAsset());
	// 资源1引用的资源3，是一个软引用，所以资源3不会被加载
	TestNull("Asset3.FastGetAsset() == nullptr", Asset3.FastGetAsset());
	
	const UBlueprint* Blueprint = Cast<UBlueprint>(Asset1.GetAsset());
	TestNotNull("Cast<UBlueprintGeneratedClass>", Blueprint);
	const UMyObject* MyObject1 = Blueprint->GeneratedClass->GetDefaultObject<UMyObject>();
	TestNotNull("Cast<UMyObject>(Asset1.GetAsset())", MyObject1);
	
	const UClass* RefClass = MyObject1->SoftRefClass.LoadSynchronous();
	TestNotNull("MyObject1->SoftRefClass.LoadSynchronous()", RefClass);

	// 此时资源3会被加载
	TestNotNull("Asset3.FastGetAsset() != nullptr", Asset3.FastGetAsset());
	
	return true;
}