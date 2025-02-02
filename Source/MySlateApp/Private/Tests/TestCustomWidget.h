#pragma once

#include "TestManager.h"

class FTestCustomWidgetImpl;

class FTestCustomWidget : public FUiTestBase
{
public:
	FTestCustomWidget();
	virtual ~FTestCustomWidget() override;
	virtual FName GetName() const override;	
	virtual TSharedRef<SWidget> CreateWidget() const override;

private:
	TSharedPtr<FTestCustomWidgetImpl> Impl;
};
