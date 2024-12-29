#pragma once

#include "CoreMinimal.h"

class FMyAssetEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;
};
