#include "CQTest.h"
#include "TestUe/Test/MyObject.h"
#include "PackageTools.h"
#include "UObject/SavePackage.h"

namespace
{
    void get_all_loaded_packages(TSet<FString>& result)
    {
        for (TObjectIterator<UPackage> it; it; ++it)
        {
            result.Add(it->GetName());
        }
    }    

    void try_create_package_for_test(const FString& package_name, const FString& file_path)
    {
        if (IFileManager::Get().FileExists(*file_path))
        {
            return;
        }

        UPackage* package = CreatePackage(*package_name);
        check(package);

        UMyObject* my_object1 = NewObject<UMyObject>(package, UMyObject::StaticClass(), TEXT("MyObject1"), RF_Public | RF_Standalone);
        my_object1->PlayerHealth = 100;
        UMyObject* my_object2 = NewObject<UMyObject>(package, UMyObject::StaticClass(), TEXT("MyObject2"), RF_Public | RF_Standalone);
        my_object2->PlayerHealth = 200;
        my_object2->RefObject = my_object1;
        my_object1->RefObject = my_object2;
        package->SetDirtyFlag(true);

        FSavePackageArgs save_package_args;
        save_package_args.TopLevelFlags = RF_Public | RF_Standalone;

        const FSavePackageResultStruct result = UPackage::Save(package, nullptr, *file_path, save_package_args);
        check(result.Result == ESavePackageResult::Success);
    }
}

TEST_CLASS(Package, "TestUe")
{
    TEST_METHOD(LoadTest)
    {
        // 创建
        const FString ShortName = TEXT("MyTestPackage1");
        const FString PackageName = FString::Printf(TEXT("/Game/MyTest/%s"), *ShortName);
        const FString FilePath = FString::Printf(TEXT("%s%s%s.uasset"), *FPaths::ProjectContentDir(), TEXT("MyTest/"), *ShortName);

        try_create_package_for_test(PackageName, FilePath);

        // LoadObject
        const UMyObject* MyObject1 = LoadObject<UMyObject>(nullptr, *(PackageName + TEXT(".MyObject1")));
        ASSERT_THAT(IsNotNull(MyObject1));
        ASSERT_THAT(AreEqual(MyObject1->PlayerHealth, 100));
        const UMyObject* MyObject2 = LoadObject<UMyObject>(nullptr, *(PackageName + TEXT(".MyObject2")));
        ASSERT_THAT(IsNotNull(MyObject2));
        ASSERT_THAT(AreEqual(MyObject2->PlayerHealth, 200));
        ASSERT_THAT(IsTrue(MyObject1->RefObject == MyObject2));
        ASSERT_THAT(IsTrue(MyObject2->RefObject == MyObject1));

        // 加载
        UPackage* Package = LoadPackage(nullptr, *PackageName, LOAD_None);

        // MyObject的Outer是Package
        ASSERT_THAT(IsTrue(MyObject1->GetOuter() == Package));
        ASSERT_THAT(IsTrue(MyObject1->GetOutermost() == Package));
        ASSERT_THAT(IsTrue(MyObject1->GetPackage() == Package));

        // Package中包含MyObject
        ASSERT_THAT(IsNotNull(FindObject<UMyObject>(Package, TEXT("MyObject1"))));
        ASSERT_THAT(IsNotNull(FindObject<UMyObject>(Package, TEXT("MyObject2"))));

        // 卸载 
        UPackageTools::UnloadPackages({Package});

        // 删除
        ASSERT_THAT(IsTrue(IFileManager::Get().FileExists(*FilePath)));
        IFileManager::Get().Delete(*FilePath);
        
        ASSERT_THAT(IsFalse(IFileManager::Get().FileExists(*FilePath)));
    }

    TEST_METHOD(RefTest)
    {
        // 创建
        const FString ShortName = TEXT("MyTestPackage2");
        const FString PackageName = FString::Printf(TEXT("/Game/MyTest/%s"), *ShortName);
        const FString FilePath = FString::Printf(TEXT("%s%s%s.uasset"), *FPaths::ProjectContentDir(), TEXT("MyTest/"), *ShortName);

        try_create_package_for_test(PackageName, FilePath);

        UPackage* Package = LoadPackage(nullptr, *PackageName, LOAD_None);
        FLinkerLoad* Linker = Package->GetLinker();

        // 名字表存在的作用主要是为了节省内存，避免重复存储相同的字符串
        // NameEntryId: 8 IntProperty
        // NameEntryId: 0 None
        // NameEntryId: 23 ObjectProperty
        // NameEntryId: 12395 PackageLocalizationNamespace
        // NameEntryId: 1283562 PlayerHealth
        // NameEntryId: 1283552 RefObject
        // NameEntryId: 464147 /Game/MyTest/MyTestPackage2
        // NameEntryId: 11839 /Script/CoreUObject
        // NameEntryId: 332761 /Script/TestUe
        // NameEntryId: 394 Class
        // NameEntryId: 216830 MetaData
        // NameEntryId: 485048 MyObject
        // NameEntryId: 437510 MyObject1
        // NameEntryId: 348684 MyObject2
        // NameEntryId: 539 Package
        // NameEntryId: 583 PackageMetaData
        TArray<FString> AllNames;
        for (const FNameEntryId& NameEntryId : Linker->NameMap)
        {
            const FNameEntry* NameEntry = FName::GetEntry(NameEntryId);
            AllNames.Add(NameEntry->GetPlainNameString());
        }

        const TArray<FString> ExpectedNames = { TEXT("MyObject1"), TEXT("MyObject2") };
        for (const FString& ExpectedName : ExpectedNames)
        {
            ASSERT_THAT(IsTrue(AllNames.Contains(ExpectedName)));
        }

        // 导入表记录了导入的对象的信息，包括对象的名称、类名、包名等
        // /Script/CoreUObject 表示依赖的CoreUObject模块
        // ObjectImport: MetaData /Script/CoreUObject Class
        // ObjectImport: MyObject /Script/CoreUObject Class
        // ObjectImport: /Script/CoreUObject /Script/CoreUObject Package
        // ObjectImport: /Script/TestUe /Script/CoreUObject Package
        TArray<FString> ExpectedImportNames = { TEXT("MetaData"), TEXT("MyObject"), TEXT("/Script/CoreUObject"), TEXT("/Script/TestUe") };
        for (const FString& ExpectedImportName : ExpectedImportNames)
        {
            const bool bFound = Linker->ImportMap.ContainsByPredicate([ExpectedImportName](const FObjectImport& Import) {
                return Import.ObjectName.ToString() == ExpectedImportName;
            });
            ASSERT_THAT(IsTrue(bFound));
        }

        // 导出表记录了导出的对象的信息    
        TArray<FString> ExpectedExportNames = { TEXT("PackageMetaData"), TEXT("MyObject1"), TEXT("MyObject2") };
        for (const FString& ExpectedExportName : ExpectedExportNames)
        {
            const bool bFound = Linker->ExportMap.ContainsByPredicate([ExpectedExportName](const FObjectExport& Export) {
                return Export.ObjectName.ToString() == ExpectedExportName;
            });
            ASSERT_THAT(IsTrue(bFound));
        }

        ASSERT_THAT(AreEqual(Linker->DependsMap.Num(), Linker->ExportMap.Num()));
        for (int i = 0; i < Linker->DependsMap.Num(); ++i)
        {
            ASSERT_THAT(AreEqual(Linker->DependsMap[i].Num(), 0));
        }

        // 删除
        UPackageTools::UnloadPackages({Package});
        IFileManager::Get().Delete(*FilePath);
    }

    TEST_METHOD(GetAllTest)
    {
        TSet<FString> AllLoadedPackages;
        get_all_loaded_packages(AllLoadedPackages);

        const TArray<FString> ExpectedPackages = {
            TEXT("/Engine/Transient"),
            TEXT("/Engine/EngineResources/Black"),
            TEXT("/Script/TestUe"),
            TEXT("/Script/LevelEditor")
        };
        for (const FString& ExpectedPackage : ExpectedPackages)
        {
            ASSERT_THAT(IsTrue(AllLoadedPackages.Contains(ExpectedPackage)));
        }
    }
};
