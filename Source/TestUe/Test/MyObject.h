#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyObject.generated.h"

UCLASS(Blueprintable, BlueprintType)
class TESTUE_API UMyObject : public UObject
{
	GENERATED_BODY()

public:
	static int32 FreeCount;
	static int32 NewCount;
	
	UMyObject();
	virtual ~UMyObject() override { FreeCount++; }
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
	FVector3f PlayerLocation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
	int32 PlayerHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
	TArray<int32> NumbersProperty;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
	UMyObject* RefObject;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
	TSubclassOf<UMyObject> RefClass;

	TArray<int32> Numbers;

	int32 SelfSerialNumber = 0;

	int32 NormalNumber = 0;

	virtual void Serialize(FArchive& Ar) override;
};
