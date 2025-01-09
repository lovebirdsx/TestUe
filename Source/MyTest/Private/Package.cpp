#include "Package.h"

#include "MyTest.h"
#include "UObjectIterator.h"
#include "Misc/AutomationTest.h"

namespace
{
	void GetAllLoadedPackages(TSet<FString> &Result)
	{
		for (TObjectIterator<UPackage> It; It; ++It)
		{
			Result.Add(It->GetName());
		}
	}
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(TestPackage_GetAll, "MyTest.Package.GetAll", TEST_FILTER)

bool TestPackage_GetAll::RunTest(const FString& Parameters)
{
	TSet<FString> Packages;
	GetAllLoadedPackages(Packages);
	TestGreaterThan("Packages must not be empty", Packages.Num(), 0);
	
	const TArray<FString> ExpectedPackages =
	{
		TEXT("/Script/MyTest"),
		TEXT("/Engine/Transient")
	};

	for (const FString& ExpectedPackage : ExpectedPackages)
	{
		TestTrue("Package must be in the expected list: " + ExpectedPackage, Packages.Contains(ExpectedPackage));
	}	

	return true;
}
