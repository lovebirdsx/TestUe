#include "CustomGraphSchema3.h"

#define LOCTEXT_NAMESPACE "UCustomGraphSchema3"

void UCustomGraphSchema3::GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	if (Context->Node)
	{
		{			
			FToolMenuSection& Section = Menu->AddSection("Nodes", LOCTEXT("NodeActionsNodes", "Nodes"));

			TSharedPtr<FNewNodeAction> NewNodeAction(new FNewNodeAction(
				FText::FromString(TEXT("Nodes")),
				FText::FromString(TEXT("New node")),
				FText::FromString(TEXT("Create a new node")),
				0
			));			
		}
	}	

	Super::GetContextMenuActions(Menu, Context);
}

UEdGraphNode* FNewNodeAction::PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location,
	bool bSelectNewNode)
{
	UEdGraphNode* NewNode = NewObject<UEdGraphNode>(ParentGraph);
	NewNode->NodePosX = Location.X;
	NewNode->NodePosY = Location.Y;

	NewNode->CreatePin(
		EGPD_Input,
		FName(TEXT("Inputs")),
		FName(TEXT("SomeInput"))
	);

	NewNode->CreatePin(
		EGPD_Output,
		FName(TEXT("Outputs")),
		FName(TEXT("Output1"))
	);

	NewNode->CreatePin(
		EGPD_Output,
		FName(TEXT("Outputs")),
		FName(TEXT("Output2"))
	);

	ParentGraph->Modify();
	ParentGraph->AddNode(NewNode, true, true);
	
	return NewNode;
}

#undef LOCTEXT_NAMESPACE