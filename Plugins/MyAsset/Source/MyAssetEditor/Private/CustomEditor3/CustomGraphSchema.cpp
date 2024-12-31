#include "CustomEditor3/CustomGraphSchema.h"
#include "CustomEditor3/CustomGraphNodeAction.h"

#define LOCTEXT_NAMESPACE "UCustomGraphSchema"

void UCustomGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{	
	const TSharedPtr<FNewNodeAction> NewNodeAction(new FNewNodeAction(
		FText::FromString(TEXT("Nodes")),
		FText::FromString(TEXT("New node")),
		FText::FromString(TEXT("Create a new node")),
		0
	));	

	ContextMenuBuilder.AddAction(NewNodeAction);	
}

const FPinConnectionResponse UCustomGraphSchema::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
{
	if (A == nullptr || B == nullptr)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Pins are null"));
	}

	if (A->Direction == B->Direction)
	{
		return FPinConnectionResponse(CONNECT_RESPONSE_DISALLOW, TEXT("Cannot connect two pins of the same direction"));
	}

	return FPinConnectionResponse(CONNECT_RESPONSE_MAKE, TEXT(""));
}

#undef LOCTEXT_NAMESPACE