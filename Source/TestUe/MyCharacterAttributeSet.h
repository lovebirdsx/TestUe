// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "MyCharacterAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * 
 */
UCLASS()
class TESTUE_API UMyCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FGameplayAttributeData Health = 100.0f;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, Health)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttributeData Armor = 100.0f;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, Armor)

	UPROPERTY()
	FGameplayAttributeData Damage = 100.0f;
	ATTRIBUTE_ACCESSORS(UMyCharacterAttributeSet, Damage)
};
