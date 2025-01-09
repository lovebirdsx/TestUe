#include "MyTest.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_AssetManager, "MyTest.Asset.AssetManager", TEST_FILTER)

bool TestAsset_AssetManager::RunTest(const FString& Parameters)
{		
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestAsset_AssetRegistry, "MyTest.Asset.AssetRegistry", TEST_FILTER)

bool TestAsset_AssetRegistry::RunTest(const FString& Parameters)
{
	
	return true;
}

