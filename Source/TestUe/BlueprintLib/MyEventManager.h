// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyEventManager.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnLiveCodingCompleteDelegate);

UCLASS(Blueprintable, BlueprintType)
class TESTUE_API UMyEventManager : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintAssignable, Category = "TestUe Events")
	FOnLiveCodingCompleteDelegate OnLiveCodingComplete;

	static UMyEventManager* GetInstance();
	void TriggerLiveCodingComplete();

private:
	void Init();
};
