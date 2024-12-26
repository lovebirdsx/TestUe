// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyBpParent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MYBLUEPRINT_API UMyBpParent : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "MyBpParent")
	void Test();
};
