#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "DataRegistryId.h"
#include "GameplayTagContainer.h"
#include "MyObject.generated.h"

// 标记为DefaultToInstanced，可以内联创建，譬如该对象作为属性，可以无需多创建一个资源
// 具体案例可以参考，BP_MyObject1.uasset种的用法：UMyDataBase对象可以内联创建，也可以引用资源
UCLASS(Abstract, DefaultToInstanced, EditInlineNew)
class TESTUE_API UMyDataBase : public UObject
{
    GENERATED_BODY()
};

// 标记为BlueprintType和Blueprintable，编辑器可以构造基于该c++类型的蓝图
UCLASS(Blueprintable, BlueprintType)
class TESTUE_API UMyData1 : public UMyDataBase
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    int32 Value;
};

UCLASS(Blueprintable, BlueprintType)
class TESTUE_API UMyData2 : public UMyDataBase
{
    GENERATED_BODY()
public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    FString Name;
};

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
    UMyObject *RefObject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    TSubclassOf<UMyObject> RefClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    TSoftClassPtr<UMyObject> SoftRefClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    FDataRegistryId RefDataId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    TArray<UMyDataBase *> DataArray;

    TArray<int32> Numbers;

    int32 SelfSerialNumber = 0;

    int32 NormalNumber = 0;

    virtual void Serialize(FArchive &Ar) override;

#if WITH_EDITOR
    virtual EDataValidationResult IsDataValid(class FDataValidationContext &Context) const;
#endif // WITH_EDITOR
};

USTRUCT(BlueprintType)
struct TESTUE_API FMyStruct
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    int32 Value = 0;
};

USTRUCT(BlueprintType)
struct TESTUE_API FMyTableRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    FGameplayTag Tag;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    int32 Value = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TestUe")
    TSubclassOf<UMyObject> RefClass;
};
