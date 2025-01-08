// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBPLib.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TESTUE_API UMyBPLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable, Category = "TestUe")
	static FString GetPackageName(UObject* Object);
};
