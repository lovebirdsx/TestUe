#include "CustomEditor3/CustomGraphOperations.h"

#include "CustomRuntimeGraph.h"
#include "CustomEditor3/CustomGraphNode.h"

void FCustomGraphOperations::RuntimeGraphToUIGraph(const UCustomRuntimeGraph* InRuntimeGraph, UEdGraph* InUIGraph)
{
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;	

	for (UCustomRuntimeNode* RuntimeNode : InRuntimeGraph->Nodes)
	{
		UCustomGraphNode *NewNode = NewObject<UCustomGraphNode>(InUIGraph);
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;

		if (RuntimeNode->InputPin != nullptr)
		{
			UCustomRuntimePin *Pin = RuntimeNode->InputPin;
			UEdGraphPin *UiPin = NewNode->CreateCustomPin(EGPD_Input, Pin->Name);
			UiPin->PinId = Pin->Id;
			IdToPinMap.Add(RuntimeNode->InputPin->Id, UiPin);

			if (Pin->ConnectedTo != nullptr)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->Id, Pin->ConnectedTo->Id);
				Connections.Add(Connection);
			}
		}

		for (UCustomRuntimePin *Pin : RuntimeNode->OutputPins)
		{
			UEdGraphPin *UiPin = NewNode->CreateCustomPin(EGPD_Output, Pin->Name);
			UiPin->PinId = Pin->Id;
			IdToPinMap.Add(Pin->Id, UiPin);

			if (Pin->ConnectedTo != nullptr)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->Id, Pin->ConnectedTo->Id);
				Connections.Add(Connection);
			}
		}

		InUIGraph->AddNode(NewNode, true, true);
	}

	for (const auto & [first, second] : Connections)
	{
		UEdGraphPin *FromPin = IdToPinMap[first];
		UEdGraphPin *ToPin = IdToPinMap[second];
		FromPin->LinkedTo.Add(ToPin);
		ToPin->LinkedTo.Add(FromPin);
	}
}

void FCustomGraphOperations::UIGraphToRuntimeGraph(const UEdGraph *InUIGraph, UCustomRuntimeGraph *InRuntimeGraph)
{
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UCustomRuntimePin*> IdToPinMap;

	InRuntimeGraph->Nodes.Empty();

	for (UEdGraphNode *UiNode : InUIGraph->Nodes)
	{
		UCustomRuntimeNode *RuntimeNode = NewObject<UCustomRuntimeNode>();
		RuntimeNode->Position = FVector2d(UiNode->NodePosX, UiNode->NodePosY);

		for (UEdGraphPin *UiPin: UiNode->Pins)
		{
			UCustomRuntimePin *RuntimePin = NewObject<UCustomRuntimePin>();
			RuntimePin->Name = UiPin->PinName;
			RuntimePin->Id = UiPin->PinId;

			if (UiPin->HasAnyConnections() && UiPin->Direction == EGPD_Output)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(UiPin->PinId, UiPin->LinkedTo[0]->PinId);
				Connections.Add(Connection);
			}

			IdToPinMap.Add(UiPin->PinId, RuntimePin);
			if (UiPin->Direction == EGPD_Input)
			{
				RuntimeNode->InputPin = RuntimePin;
			}
			else
			{
				RuntimeNode->OutputPins.Add(RuntimePin);
			}
		}

		InRuntimeGraph->Nodes.Add(RuntimeNode);
	}

	for (const auto & [first, second] : Connections)
	{
		UCustomRuntimePin *FromPin = IdToPinMap[first];
		UCustomRuntimePin *ToPin = IdToPinMap[second];
		FromPin->ConnectedTo = ToPin;
	}
}
