#include "CustomEditor3/CustomGraphSchema3.h"
#include "CustomEditor3/CustomGraphNodeAction3.h"

#define LOCTEXT_NAMESPACE "UCustomGraphSchema3"

void UCustomGraphSchema3::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{	
	const TSharedPtr<FNewNodeAction3> NewNodeAction(new FNewNodeAction3(
		FText::FromString(TEXT("Nodes")),
		FText::FromString(TEXT("New node")),
		FText::FromString(TEXT("Create a new node")),
		0
	));	

	ContextMenuBuilder.AddAction(NewNodeAction);	
}

const FPinConnectionResponse UCustomGraphSchema3::CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const
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