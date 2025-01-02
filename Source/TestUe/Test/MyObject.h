#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyObject.generated.h"

UCLASS()
class TESTUE_API UMyObject : public UObject
{
	GENERATED_BODY()

public:
	static int32 FreeCount;
	static int32 NewCount;
	
	UMyObject();
	virtual ~UMyObject() override { FreeCount++; }
	
	UPROPERTY()
	FVector3f PlayerLocation;

	UPROPERTY()
	int32 PlayerHealth;

	UPROPERTY()
	TArray<int32> NumbersProperty;

	TArray<int32> Numbers;

	int32 SelfSerialNumber = 0;

	int32 NormalNumber = 0;

	virtual void Serialize(FArchive& Ar) override;
};
