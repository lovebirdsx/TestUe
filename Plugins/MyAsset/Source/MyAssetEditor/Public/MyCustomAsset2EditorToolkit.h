#pragma once

#include "CoreMinimal.h"
#include "Toolkits/AssetEditorToolkit.h"

class UMyCustomAsset2;

class FMyCustomAsset2EditorToolkit : public FAssetEditorToolkit
{
public:
	void InitEditor(const FAssetOpenArgs& OpenArgs);

	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FName GetToolkitFName() const override { return "MyCustomAssetEditor"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("My Custom Asset Editor"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "My Custom Asset Editor"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
private:
	UMyCustomAsset2* Asset = nullptr;
};
