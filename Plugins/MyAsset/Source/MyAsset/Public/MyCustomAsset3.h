﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyCustomAsset3.generated.h"

class UCustomRuntimeGraph3;

UCLASS(BlueprintType)
class MYASSET_API UMyCustomAsset3 : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32 AssetValue;

	UPROPERTY()
	UCustomRuntimeGraph3* RuntimeGraph = nullptr;
};
