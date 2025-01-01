#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "CustomGraphNodeAction3.generated.h"

USTRUCT()
struct FNewNodeAction3: public FEdGraphSchemaAction
{
	GENERATED_BODY()

	FNewNodeAction3() {}
	FNewNodeAction3(const FText& InNodeCategory, const FText& InMenuDesc, const FText& InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping)
	{
	}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};
