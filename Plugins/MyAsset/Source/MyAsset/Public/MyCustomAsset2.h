#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyCustomAsset2.generated.h"

UCLASS(BlueprintType)
class MYASSET_API UMyCustomAsset2 : public UObject
{
	GENERATED_BODY()

public:
	UMyCustomAsset2();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	FString AssetName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Custom")
	int32 AssetValue;
};
