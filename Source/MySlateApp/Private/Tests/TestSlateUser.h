#pragma once

#include "TestManager.h"

class FTestSlateUserImpl;

class FTestSlateUser : public FUiTestBase
{
public:
	FTestSlateUser();
	virtual ~FTestSlateUser() override;
	virtual FName GetName() const override;	
	virtual TSharedRef<SWidget> CreateWidget() const override;

private:
	TSharedPtr<FTestSlateUserImpl> Impl;
};
