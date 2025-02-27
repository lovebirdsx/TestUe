#include "CQTest.h"
#include "TestUe/Test/MyObject.h"
#include "PackageTools.h"
#include "Engine/AssetManager.h"
#include "TestCommon.h" // 包含 FMyTestCommand_WaitLoadPrimaryAsset

TEST_CLASS(Asset, "TestUe")
{
    TEST_METHOD(AssetManagerTest)
    {
        UAssetManager* AssetManager = UAssetManager::GetIfInitialized();
        ASSERT_THAT(IsNotNull(AssetManager));

        const FPrimaryAssetId PrimaryAssetId = FPrimaryAssetId("MyObject", "BP_MyObject1");
        const FSoftObjectPath Path = AssetManager->GetPrimaryAssetPath(PrimaryAssetId);
        ASSERT_THAT(IsTrue(Path.IsValid()));
        ASSERT_THAT(AreEqual(Path.ToString(), "/Game/MyTest/BP_MyObject1.BP_MyObject1_C"));        

        AssetManager->LoadPrimaryAsset(PrimaryAssetId, {}, FStreamableDelegate::CreateLambda([this, AssetManager, PrimaryAssetId]()
        {
            UObject* Asset1 = AssetManager->GetPrimaryAssetObject(PrimaryAssetId);
            ASSERT_THAT(IsNotNull(Asset1));
            
            UBlueprintGeneratedClass* BlueprintClass = Cast<UBlueprintGeneratedClass>(Asset1);
            const UMyObject* MyObjectInstance = NewObject<UMyObject>(GetTransientPackage(), BlueprintClass);
            ASSERT_THAT(IsNotNull(MyObjectInstance));
            ASSERT_THAT(AreEqual(MyObjectInstance->PlayerHealth, 101));

            const FPrimaryAssetId PrimaryAssetId2 = FPrimaryAssetId("MyObject", "BP_MyObject2");
            ASSERT_THAT(IsNotNull(AssetManager->GetPrimaryAssetObject(PrimaryAssetId2)));

            AssetManager->UnloadPrimaryAsset(PrimaryAssetId);
        }));

        AddCommand(new FMyTestCommand_WaitLoadPrimaryAsset(PrimaryAssetId));        
    }

    TEST_METHOD(AssetRegistryTest)
    {
        const IAssetRegistry& AssetRegistry = IAssetRegistry::GetChecked();
        FARFilter Filter;
        Filter.ClassPaths.Add(UMyObject::StaticClass()->GetClassPathName());
        Filter.bRecursiveClasses = true;

        TArray<FAssetData> AssetDataList;
        AssetRegistry.GetAssets(Filter, AssetDataList);
        ASSERT_THAT(AreEqual(AssetDataList.Num(), 0));

        const FAssetData AssetData = AssetRegistry.GetAssetByObjectPath(FSoftObjectPath(FName("/Game/MyTest/BP_MyObject1.BP_MyObject1")));
        ASSERT_THAT(IsTrue(AssetData.IsValid()));
        ASSERT_THAT(AreEqual(AssetData.AssetName.ToString(), TEXT("BP_MyObject1")));
        ASSERT_THAT(AreEqual(AssetData.PackageName.ToString(), TEXT("/Game/MyTest/BP_MyObject1")));
        ASSERT_THAT(AreEqual(AssetData.AssetClassPath.ToString(), TEXT("/Script/Engine.Blueprint")));

        const UObject* Asset = AssetData.GetAsset();
        ASSERT_THAT(IsNotNull(Asset));
        const UBlueprint* Blueprint = Cast<UBlueprint>(Asset);
        ASSERT_THAT(IsNotNull(Blueprint));
        const UMyObject* Cdo = Blueprint->GeneratedClass->GetDefaultObject<UMyObject>();
        ASSERT_THAT(IsNotNull(Cdo));

        ASSERT_THAT(AreEqual(Cdo->PlayerHealth, 101));
    }

    TEST_METHOD(AssetLoadTest)
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

        ASSERT_THAT(IsTrue(Asset1.IsValid()));
        ASSERT_THAT(IsTrue(Asset2.IsValid()));
        ASSERT_THAT(IsTrue(Asset3.IsValid()));

        // 先确保资源未加载
        UPackageTools::UnloadPackages({Asset1.GetPackage(), Asset2.GetPackage(), Asset3.GetPackage()});

        ASSERT_THAT(IsNull(Asset1.FastGetAsset()));
        ASSERT_THAT(IsNull(Asset2.FastGetAsset()));
        ASSERT_THAT(IsNull(Asset3.FastGetAsset()));

        // 加载资源1（同步）
        UPackageTools::LoadPackage(PackageName1.ToString());

        ASSERT_THAT(IsNotNull(Asset1.FastGetAsset()));
        ASSERT_THAT(IsNotNull(Asset2.FastGetAsset()));
        ASSERT_THAT(IsNull(Asset3.FastGetAsset()));

        const UBlueprint* Blueprint = Cast<UBlueprint>(Asset1.GetAsset());
        ASSERT_THAT(IsNotNull(Blueprint));
        const UMyObject* MyObject1 = Blueprint->GeneratedClass->GetDefaultObject<UMyObject>();
        ASSERT_THAT(IsNotNull(MyObject1));

        const UClass* RefClass = MyObject1->SoftRefClass.LoadSynchronous();
        ASSERT_THAT(IsNotNull(RefClass));

        ASSERT_THAT(IsNotNull(Asset3.FastGetAsset()));
    }
};
