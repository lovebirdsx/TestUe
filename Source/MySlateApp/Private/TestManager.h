#pragma once

#include "CoreMinimal.h"
#include "SWidget.h"

class FUiTestBase
{
public:
	virtual ~FUiTestBase() = default;

	virtual FName GetName() const = 0;
	virtual TSharedRef<SWidget> CreateWidget() const = 0;
};

class FTestManager
{
public:
	void GetAllNames(TArray<FName>& OutNames) const;

	TSharedPtr<FUiTestBase> GetTest(const FName& TestName) const;
	
	void RegisterTest(TSharedPtr<FUiTestBase> Test);

private:
	TMap<FName, TSharedPtr<FUiTestBase>> Tests;
};