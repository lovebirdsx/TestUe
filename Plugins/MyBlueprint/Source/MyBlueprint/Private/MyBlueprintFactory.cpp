// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFactory.h"

#include "MyBlueprint.h"
#include "MyBpParent.h"
#include "Kismet2/KismetEditorUtilities.h"

UMyBlueprintFactory::UMyBlueprintFactory()
{
	bCreateNew = true;
	bEditAfterNew = true;
	SupportedClass = UMyBlueprint::StaticClass();
	ParentClass = UMyBpParent::StaticClass();
}

bool UMyBlueprintFactory::ConfigureProperties()
{
	return true;
}

UObject* UMyBlueprintFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
                                               UObject* Context, FFeedbackContext* Warn)
{
	UMyBlueprint* NewBp = NewObject<UMyBlueprint>(InParent, InClass, InName, Flags);
	NewBp->ParentClass = ParentClass;

	FKismetEditorUtilities::CreateBlueprint(ParentClass, InParent, InName, BPTYPE_Normal, UMyBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), TEXT("MyBlueprint"));

	return NewBp;
}
