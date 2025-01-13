#pragma once

#include "TestManager.h"

class FTestButtonImpl;

class FTestButton : public FUiTestBase
{
public:
	FTestButton();
	virtual ~FTestButton() override;
	virtual FName GetName() const override;	
	virtual TSharedRef<SWidget> CreateWidget() const override;

private:
	TSharedPtr<FTestButtonImpl> Impl;
};
