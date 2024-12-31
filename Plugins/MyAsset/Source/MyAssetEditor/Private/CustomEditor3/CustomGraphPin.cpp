#include "CustomEditor3/CustomGraphPin.h"

FSlateColor SCustomGraphPin::GetPinColor() const
{
	if (GraphPinObj && GraphPinObj->Direction == EGPD_Input)
	{
		return FSlateColor(FLinearColor(0.0f, 1.0f, 1.0f));
	}
	
	return FSlateColor(FLinearColor(0.2f, 1.0f, 0.2f));
}

TSharedPtr<SGraphPin> FCustomPinFactory::CreatePin(UEdGraphPin* Pin) const
{
	if (FName(TEXT("CustomPin")) == Pin->PinType.PinSubCategory)
	{
		return SNew(SCustomGraphPin, Pin);
	}

	return nullptr;
}
