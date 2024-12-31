#pragma once

#include "EdGraphUtilities.h"
#include "SGraphPin.h"

class SCustomGraphPin : public SGraphPin
{
	SLATE_BEGIN_ARGS(SCustomGraphPin) {}		
	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UEdGraphPin* InPin)
	{
		SGraphPin::Construct(SGraphPin::FArguments(), InPin);
	}

protected:
	virtual FSlateColor GetPinColor() const override;
};

class FCustomPinFactory : public FGraphPanelPinFactory
{
public:
	virtual ~FCustomPinFactory() override {}
	virtual TSharedPtr<SGraphPin> CreatePin(UEdGraphPin* Pin) const override;
};
