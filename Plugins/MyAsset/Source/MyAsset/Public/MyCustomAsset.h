#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyCustomAsset.generated.h"

UCLASS(Blueprintable)
class MYASSET_API UMyCustomAsset : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32 AssetValue;
};
