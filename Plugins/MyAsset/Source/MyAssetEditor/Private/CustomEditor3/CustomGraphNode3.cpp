#include "CustomEditor3/CustomGraphNode3.h"

#include "ResouceManager.h"

FText UCustomGraphNode3::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("My Node Title"));
}

FLinearColor UCustomGraphNode3::GetNodeTitleColor() const
{
	return FLinearColor::Green;
}

bool UCustomGraphNode3::CanUserDeleteNode() const
{
	return true;
}

void UCustomGraphNode3::GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection(TEXT("CustomNodeActions"), FText::FromString("CustomNodeActions"));
	UCustomGraphNode3 *Node = const_cast<UCustomGraphNode3*>(this);
	Section.AddMenuEntry(
		TEXT("AddPinEntry"),
		FText::FromString("Add Pin"),
	    FText::FromString("Add a new pin"),
	    FSlateIcon(FResourceManager::StyleSetName, FResourceManager::CustomAsset3Editor_AddNodePin),
        FUIAction(
        	FExecuteAction::CreateLambda([Node] {
        		Node->GetGraph()->Modify();
        		UEdGraphPin* P = Node->CreateCustomPin(EGPD_Output, FName(TEXT("Outputs")));
				P->PinToolTip = FString("Another Output Pin");
        		Node->GetGraph()->PostEditChange();
        		Node->GetGraph()->NotifyGraphChanged();
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
						Node->GetGraph()->Modify();
						P->BreakAllPinLinks();
						Node->RemovePin(P);
						Node->GetGraph()->PostEditChange();
						
						Node->GetGraph()->NotifyGraphChanged();
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
				ParentGraph->Modify();
				ParentGraph->RemoveNode(Node);
				ParentGraph->PostEditChange();				
			})
	));
}

UEdGraphPin* UCustomGraphNode3::CreateCustomPin(const EEdGraphPinDirection Dir, const FName Name)
{
	const FName Category = (Dir == EGPD_Input) ? FName(TEXT("Inputs")) : FName(TEXT("Outputs"));
	const FName SubCategory = TEXT("CustomPin");

	UEdGraphPin* NewPin = CreatePin(Dir, Category, Name);
	NewPin->PinType.PinSubCategory = SubCategory;
	NewPin->PinType.PinCategory = Category;
	NewPin->PinType.PinSubCategoryObject = nullptr;

	return NewPin;
}
