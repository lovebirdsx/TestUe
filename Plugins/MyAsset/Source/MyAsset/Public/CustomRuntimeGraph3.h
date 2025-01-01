#pragma once

#include "CoreMinimal.h"
#include "UObject/NameTypes.h"
#include "CustomRuntimeGraph3.generated.h"

UCLASS()
class MYASSET_API UCustomRuntimePin3 : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FName Name;

	UPROPERTY()
	FGuid Id;

	UPROPERTY()
	UCustomRuntimePin3 *ConnectedTo = nullptr;
};

UCLASS()
class MYASSET_API UCustomRuntimeNode3 : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UCustomRuntimePin3 *InputPin = nullptr;

	UPROPERTY()
	TArray<UCustomRuntimePin3*> OutputPins;

	UPROPERTY()
	FVector2D Position;
};

UCLASS()
class MYASSET_API UCustomRuntimeGraph3 : public UObject
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	TArray<UCustomRuntimeNode3*> Nodes;
};
