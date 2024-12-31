#pragma once

#include "CoreMinimal.h"
#include "MyCustomAsset2Factory.generated.h"

UCLASS()
class MYASSETEDITOR_API UMyCustomAsset2Factory : public UFactory
{
	GENERATED_BODY()

public:
	UMyCustomAsset2Factory();

	virtual bool ConfigureProperties() override;

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
