#pragma once

#include "CoreMinimal.h"
#include "CustomGraphNode.generated.h"

UCLASS()
class MYASSETEDITOR_API UCustomGraphNode : public UEdGraphNode 
{
	GENERATED_BODY()
	
public:
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Dir, FName Name);
};
