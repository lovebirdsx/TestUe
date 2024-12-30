#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UMyCustomAsset3;

class FMyCustomAsset3EditorToolkit : public FAssetEditorToolkit
{
public:
	void InitEditor(const FAssetOpenArgs& OpenArgs);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FName GetToolkitFName() const override { return "MyCustomAssetEditor3"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("My Custom Asset Editor3"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "My Custom Asset Editor3"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
private:
	UMyCustomAsset3* Asset = nullptr;
};
