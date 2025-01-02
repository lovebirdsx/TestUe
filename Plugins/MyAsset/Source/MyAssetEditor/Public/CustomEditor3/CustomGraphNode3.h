#pragma once

#include "CoreMinimal.h"
#include "CustomGraphNode3.generated.h"

UCLASS()
class MYASSETEDITOR_API UCustomGraphNode3 : public UEdGraphNode 
{
	GENERATED_BODY()
	
public:
	UCustomGraphNode3();	
	
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override;
	virtual FLinearColor GetNodeTitleColor() const override;
	virtual bool CanUserDeleteNode() const override;
	virtual void GetNodeContextMenuActions(UToolMenu* Menu, UGraphNodeContextMenuContext* Context) const override;

	UEdGraphPin* CreateCustomPin(EEdGraphPinDirection Dir, FName Name);
};
