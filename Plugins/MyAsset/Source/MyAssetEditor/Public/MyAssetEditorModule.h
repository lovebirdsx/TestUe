#pragma once

#include "CoreMinimal.h"

class FCustomPinFactory3;
class FResourceManager;

class MYASSETEDITOR_API FMyAssetEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedPtr<FResourceManager> ResourceManager;
    TSharedPtr<FCustomPinFactory3> CustomPinFactory;
};
