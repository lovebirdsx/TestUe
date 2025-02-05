// Copyright Epic Games, Inc. All Rights Reserved.

#include "MyBlueprintMoudle.h"

#define LOCTEXT_NAMESPACE "FMyBlueprintModule"

void FMyBlueprintModule::StartupModule()
{
}

void FMyBlueprintModule::ShutdownModule()
{
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FMyBlueprintModule, MyBlueprint)
