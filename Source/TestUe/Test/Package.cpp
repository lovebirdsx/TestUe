#include "MyObject.h"
#include "PackageTools.h"
#include "Misc/AutomationTest.h"
#include "UObject/SavePackage.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPackage_Load, "TestUe.Package.Load", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool TestPackage_Load::RunTest(const FString& Parameters)
{
	// 创建
	const FString PackageName = TEXT("/Game/MyTest/MyObject");
	const FString FilePath = FPaths::ProjectContentDir() + TEXT("MyTest/MyObject.uasset");

	if (!IFileManager::Get().FileExists(*FilePath))
	{
		UPackage* Package = CreatePackage(*PackageName);
		TestNotNull("Package must be valid", Package);

		UMyObject* MyObject1 = NewObject<UMyObject>(Package, UMyObject::StaticClass(), TEXT("MyObject1"), RF_Public | RF_Standalone);
		MyObject1->PlayerHealth = 100;
		UMyObject* MyObject2 = NewObject<UMyObject>(Package, UMyObject::StaticClass(), TEXT("MyObject2"), RF_Public | RF_Standalone);
		MyObject2->PlayerHealth = 200;
		Package->SetDirtyFlag(true);

		// 保存
		FSavePackageArgs SavePackageArgs;
		SavePackageArgs.TopLevelFlags = RF_Public | RF_Standalone;
		
		const FSavePackageResultStruct Result = UPackage::Save(Package, nullptr, *FilePath, SavePackageArgs);

		TestEqual("Save must be successful", Result.Result, ESavePackageResult::Success);		
	}	

	// LoadObject
	const UMyObject* MyObject1 = LoadObject<UMyObject>(nullptr, *(PackageName + TEXT(".MyObject1")));
	TestNotNull("MyObject1 must be valid", MyObject1);
	TestEqual("MyObject1's PlayerHealth must be 100", MyObject1->PlayerHealth, 100);
	const UMyObject* MyObject2 = LoadObject<UMyObject>(nullptr, *(PackageName + TEXT(".MyObject2")));
	TestNotNull("MyObject2 must be valid", MyObject2);
	TestEqual("MyObject2's PlayerHealth must be 200", MyObject2->PlayerHealth, 200);
	
	// 加载
	UPackage* Package = LoadPackage(nullptr, *PackageName, LOAD_None);

	// MyObject的Outer是Package
	TestTrue("MyObject1's Outer must be Package", MyObject1->GetOuter() == Package);
	TestTrue("MyObject1's OutermostObject must be Package", MyObject1->GetOutermost() == Package);
	TestTrue("MyObject1's Package must be Package", MyObject1->GetPackage() == Package);
	
	// Package中包含MyObject	 
	TestNotNull("MyObject1 must be valid", FindObject<UMyObject>(Package, TEXT("MyObject1")));
	TestNotNull("MyObject2 must be valid", FindObject<UMyObject>(Package, TEXT("MyObject2")));
	
	// 卸载	
	TArray<UPackage*> PackagesToUnload;
	PackagesToUnload.Add(Package);
	TestTrue("Package must be loaded", Package->IsFullyLoaded());
	UPackageTools::UnloadPackages(PackagesToUnload);
	TestTrue("Package must be unloaded", !Package->IsFullyLoaded());	

	// 删除	
	TestTrue("Package file must exist: " + FilePath, IFileManager::Get().FileExists(*FilePath));
	
	IFileManager::Get().Delete(*FilePath);
	TestTrue("Package file must be deleted", !IFileManager::Get().FileExists(*FilePath));
	
	return true;
}
