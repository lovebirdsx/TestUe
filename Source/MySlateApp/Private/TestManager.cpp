#include "TestManager.h"

void FTestManager::GetAllNames(TArray<FName>& OutNames) const
{
	OutNames.Empty(Tests.Num());
	for (const auto& Test : Tests)
	{
		OutNames.Add(Test.Key);
	}
}

TSharedPtr<FUiTestBase> FTestManager::GetTest(const FName& TestName) const
{
	return Tests.FindRef(TestName);
}

void FTestManager::RegisterTest(TSharedPtr<FUiTestBase> Test)
{
	Tests.Add(Test->GetName(), Test);
}
