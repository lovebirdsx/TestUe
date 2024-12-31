#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "CustomRuntimeGraph.generated.h"

UCLASS()
class MYASSET_API UCustomRuntimePin : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	UCustomRuntimePin *ConnectedTo = nullptr;
};

UCLASS()
class MYASSET_API UCustomRuntimeNode : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UCustomRuntimePin *InputPin = nullptr;

	UPROPERTY()
	TArray<UCustomRuntimePin*> OutputPins;

	UPROPERTY()
	FVector2D Position;
};

UCLASS()
class MYASSET_API UCustomRuntimeGraph : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UCustomRuntimeNode*> Nodes;
};
