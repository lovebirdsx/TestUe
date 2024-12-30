#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "CustomGraphSchema3.generated.h"

UCLASS()
class MYASSETEDITOR_API UCustomGraphSchema3 : public UEdGraphSchema
{
	GENERATED_BODY()
	
public:
	virtual void GetContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;
};

USTRUCT()
struct FNewNodeAction: public FEdGraphSchemaAction
{
	GENERATED_BODY()

	FNewNodeAction() {}
	FNewNodeAction(FText InNodeCategory, FText InMenuDesc, FText InToolTip, const int32 InGrouping)
		: FEdGraphSchemaAction(InNodeCategory, InMenuDesc, InToolTip, InGrouping)
	{
	}

	virtual UEdGraphNode* PerformAction(class UEdGraph* ParentGraph, UEdGraphPin* FromPin, const FVector2D Location, bool bSelectNewNode = true) override;
};
