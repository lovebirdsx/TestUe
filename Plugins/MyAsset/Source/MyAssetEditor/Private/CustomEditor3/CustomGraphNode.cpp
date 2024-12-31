#include "CustomEditor3/CustomGraphNode.h"

#include "ResouceManager.h"

FText UCustomGraphNode::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("My Node Title"));
}

FLinearColor UCustomGraphNode::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

bool UCustomGraphNode::CanUserDeleteNode() const
{
	return true;
}

void UCustomGraphNode::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("CustomNodeActions"), FText::FromString("CustomNodeActions"));
	UCustomGraphNode *Node = const_cast<UCustomGraphNode*>(this);
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString("Add Pin"),
	    FText::FromString("Add a new pin"),
	    FSlateIcon(FResourceManager::StyleSetName, FResourceManager::CustomAsset3Editor_AddNodePin),
        FUIAction(
        	FExecuteAction::CreateLambda([Node] {
        		UEdGraphPin* P = Node->CreateCustomPin(EGPD_Output, FName(TEXT("Outputs")));
				P->PinToolTip = FString("Another Output Pin");        		
        		Node->GetGraph()->NotifyGraphChanged();
        		Node->GetGraph()->Modify();
			})
    ));

	Section.AddMenuEntry(
		TEXT("DeletePinEntry"),
		FText::FromString("Delete Pin"),
	    FText::FromString("Delete the last out pin"),
	    FSlateIcon(FResourceManager::StyleSetName, FResourceManager::CustomAsset3Editor_DeleteNodePin),
        FUIAction(
        	FExecuteAction::CreateLambda([Node] {
        		if (Node->Pins.Num() > 0)
				{
					if (UEdGraphPin* P = Node->Pins.Last(); P->Direction == EGPD_Output)
					{
						P->BreakAllPinLinks();
						Node->RemovePin(P);
						Node->GetGraph()->NotifyGraphChanged();
						Node->GetGraph()->Modify();
					}					
				}
			})
    ));

	Section.AddMenuEntry(
		TEXT("DeleteNodeEntry"),
		FText::FromString("Delete Node"),
		FText::FromString("Delete the node"),
		FSlateIcon(FResourceManager::StyleSetName, FResourceManager::CustomAsset3Editor_DeleteNode),
		FUIAction(
			FExecuteAction::CreateLambda([Node] {
				UEdGraph* ParentGraph = Node->GetGraph();
				ParentGraph->RemoveNode(Node);
				ParentGraph->NotifyGraphChanged();
				ParentGraph->Modify();
			})
	));
}

UEdGraphPin* UCustomGraphNode::CreateCustomPin(const EEdGraphPinDirection Dir, const FName Name)
{
	const FName Category = (Dir == EGPD_Input) ? FName(TEXT("Inputs")) : FName(TEXT("Outputs"));
	const FName SubCategory = TEXT("CustomPin");

	UEdGraphPin* NewPin = CreatePin(Dir, Category, Name);
	NewPin->PinType.PinSubCategory = SubCategory;
	NewPin->PinType.PinCategory = Category;
	NewPin->PinType.PinSubCategoryObject = nullptr;

	return NewPin;
}
