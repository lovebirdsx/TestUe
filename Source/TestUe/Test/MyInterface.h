#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "MyInterface.generated.h"

UINTERFACE(Blueprintable)
class UMyInterface : public UInterface
{
    GENERATED_BODY()
};

class IMyInterface
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "MyInterface")
    void Call();
};

UCLASS(Blueprintable)
class TESTUE_API AMyInterfaceActor : public AActor, public IMyInterface
{
    GENERATED_BODY()
};
