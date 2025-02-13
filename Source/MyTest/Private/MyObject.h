#pragma once

#include "CoreMinimal.h"
#include "MyObject.generated.h"

UCLASS()
class UMyObject : public UObject
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

    virtual void Serialize(FArchive &Ar) override;
};

UCLASS()
class UOiObject1 : public UObject
{
    GENERATED_BODY()

public:
    explicit UOiObject1(const FObjectInitializer &ObjectInitializer);
};

UCLASS()
class UOiObject2 : public UObject
{
    GENERATED_BODY()

public:
    explicit UOiObject2(const FObjectInitializer &ObjectInitializer);

    UPROPERTY()
    UOiObject1 *Object1;
};

UCLASS()
class UMyObjectBase : public UObject
{
    GENERATED_BODY()
};

UCLASS()
class UMyObjectDerived1 : public UMyObjectBase
{
    GENERATED_BODY()
};

UCLASS()
class UMyObjectDerived2 : public UMyObjectBase
{
    GENERATED_BODY()
};

UCLASS(Config = MyObject)
class UMyCdoObject : public UObject
{
    GENERATED_BODY()
public:
    UMyCdoObject();

    UPROPERTY(Config)
    int32 Value;
};
