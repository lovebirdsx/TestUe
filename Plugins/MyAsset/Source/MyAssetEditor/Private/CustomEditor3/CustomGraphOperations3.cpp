#include "CustomEditor3/CustomGraphOperations3.h"

#include "CustomRuntimeGraph3.h"
#include "CustomEditor3/CustomGraphNode3.h"

void FCustomGraphOperations3::RuntimeGraphToUIGraph(const UCustomRuntimeGraph3* InRuntimeGraph, UEdGraph* InUIGraph)
{
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UEdGraphPin*> IdToPinMap;	

	for (UCustomRuntimeNode3* RuntimeNode : InRuntimeGraph->Nodes)
	{
		UCustomGraphNode3 *NewNode = NewObject<UCustomGraphNode3>(InUIGraph);
		NewNode->CreateNewGuid();
		NewNode->NodePosX = RuntimeNode->Position.X;
		NewNode->NodePosY = RuntimeNode->Position.Y;

		if (RuntimeNode->InputPin != nullptr)
		{
			UCustomRuntimePin3 *Pin = RuntimeNode->InputPin;
			UEdGraphPin *UiPin = NewNode->CreateCustomPin(EGPD_Input, Pin->Name);
			UiPin->PinId = Pin->Id;
			IdToPinMap.Add(RuntimeNode->InputPin->Id, UiPin);

			if (Pin->ConnectedTo != nullptr)
			{
				std::pair<FGuid, FGuid> Connection = std::make_pair(Pin->Id, Pin->ConnectedTo->Id);
				Connections.Add(Connection);
			}
		}

		for (UCustomRuntimePin3 *Pin : RuntimeNode->OutputPins)
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

void FCustomGraphOperations3::UIGraphToRuntimeGraph(const UEdGraph *InUIGraph, UCustomRuntimeGraph3 *InRuntimeGraph)
{
	TArray<std::pair<FGuid, FGuid>> Connections;
	TMap<FGuid, UCustomRuntimePin3*> IdToPinMap;

	InRuntimeGraph->Nodes.Empty();

	for (UEdGraphNode *UiNode : InUIGraph->Nodes)
	{
		UCustomRuntimeNode3 *RuntimeNode = NewObject<UCustomRuntimeNode3>();
		RuntimeNode->Position = FVector2d(UiNode->NodePosX, UiNode->NodePosY);

		for (UEdGraphPin *UiPin: UiNode->Pins)
		{
			UCustomRuntimePin3 *RuntimePin = NewObject<UCustomRuntimePin3>();
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
		UCustomRuntimePin3 *FromPin = IdToPinMap[first];
		UCustomRuntimePin3 *ToPin = IdToPinMap[second];
		FromPin->ConnectedTo = ToPin;
	}
}
