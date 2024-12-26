#pragma once

#include "CoreMinimal.h"
#include "Factories/BlueprintFactory.h"
#include "MyBlueprintFactory.generated.h"

UCLASS()
class MYBLUEPRINT_API UMyBlueprintFactory : public UBlueprintFactory
{
	GENERATED_BODY()

public:
	UMyBlueprintFactory();

	virtual bool ConfigureProperties() override;

	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
