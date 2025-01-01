#include "CustomEditor3/CustomGraphNodeAction3.h"
#include "CustomEditor3/CustomGraphNode3.h"

UEdGraphNode* FNewNodeAction::PerformAction(UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode)
{
	UCustomGraphNode3* N = NewObject<UCustomGraphNode3>(ParentGraph);
	N->CreateNewGuid();
	N->NodePosX = Location.X;
	N->NodePosY = Location.Y;

	UEdGraphPin* InputPin = N->CreateCustomPin(EGPD_Input, FName(TEXT("Inputs")));
	N->CreateCustomPin(EGPD_Output, FName(TEXT("Output1")));
	N->CreateCustomPin(EGPD_Output, FName(TEXT("Output2")));

	if (FromPin != nullptr)
	{
		N->GetSchema()->TryCreateConnection(FromPin, InputPin);
	}

	ParentGraph->Modify();
	ParentGraph->AddNode(N, true, true);
	
	return N;
}
