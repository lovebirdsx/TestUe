#pragma once

#include "CoreMinimal.h"
#include "MyCustomAsset3Factory.generated.h"

UCLASS()
class MYASSETEDITOR_API UMyCustomAsset3Factory : public UFactory
{
	GENERATED_BODY()

public:
	UMyCustomAsset3Factory();

	virtual bool ConfigureProperties() override;

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
