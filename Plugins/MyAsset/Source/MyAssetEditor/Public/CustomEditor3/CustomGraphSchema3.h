#pragma once

#include "CoreMinimal.h"
#include "EdGraph/EdGraph.h"
#include "CustomGraphSchema3.generated.h"

UCLASS()
class MYASSETEDITOR_API UCustomGraphSchema3 : public UEdGraphSchema
{
	GENERATED_BODY()
	
public:
	virtual void GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const override;
	virtual const FPinConnectionResponse CanCreateConnection(const UEdGraphPin* A, const UEdGraphPin* B) const override;
};

