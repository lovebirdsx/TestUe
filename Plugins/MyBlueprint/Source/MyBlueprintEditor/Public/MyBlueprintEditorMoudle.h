#pragma once

#include "Modules/ModuleManager.h"

class FMyBlueprintEditorModule : public IModuleInterface
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:
	TArray<TSharedPtr<class FAssetTypeActions_MyBlueprint>> CreatedAssetTypeActions;
};
