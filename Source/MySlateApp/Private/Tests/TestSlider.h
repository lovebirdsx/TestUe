#pragma once

#include "TestManager.h"

class FTestSliderImpl;

class FTestSlider : public FUiTestBase
{
public:
	FTestSlider();
	virtual ~FTestSlider() override;
	virtual FName GetName() const override;	
	virtual TSharedRef<SWidget> CreateWidget() const override;

private:
	TSharedPtr<FTestSliderImpl> Impl;
};
