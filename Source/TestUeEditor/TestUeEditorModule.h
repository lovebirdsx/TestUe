// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Modules/ModuleManager.h"

class TESTUEEDITOR_API FTestUeEditor : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:	
	void OnLiveCodingComplete();
	void OnBlueprintReinstanced();
	void OnEditorInitialized(double Duration);
};


