#pragma once

#include "TestManager.h"

class FTestModalWindowImpl;

class FTestModalWindow : public FUiTestBase
{
public:
	FTestModalWindow();
	virtual ~FTestModalWindow() override;
	virtual FName GetName() const override;
	virtual TSharedRef<SWidget> CreateWidget() const override;

private:
	TSharedPtr<FTestModalWindowImpl> Impl;
};
