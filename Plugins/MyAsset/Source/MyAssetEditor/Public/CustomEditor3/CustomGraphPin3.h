#pragma once

#include "EdGraphUtilities.h"
#include "SGraphPin.h"

class SCustomGraphPin3 : public SGraphPin
{
	SLATE_BEGIN_ARGS(SCustomGraphPin3) {}		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InPin);
	}

protected:
	virtual FSlateColor GetPinColor() const override;
};

class FCustomPinFactory3 : public FGraphPanelPinFactory
{
public:
	virtual ~FCustomPinFactory3() override {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override;
};
