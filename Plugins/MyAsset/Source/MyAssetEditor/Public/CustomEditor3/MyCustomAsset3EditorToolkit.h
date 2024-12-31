#pragma once

#include "CoreMinimal.h"
#include "MyCustomAsset3EditorState.h"
#include "Toolkits/AssetEditorToolkit.h"

class UMyCustomAsset3;

class FMyCustomAsset3EditorToolkit : public FAssetEditorToolkit, public IMyCustomAsset3EditorState
{
public:
	void InitEditor(const FAssetOpenArgs& OpenArgs);

	// IMyCustomAsset3EditorState Begin
	virtual UMyCustomAsset3* GetAsset() override { return Asset; }
	virtual UEdGraph* GetGraph() override { return Graph; }
	// IMyCustomAsset3EditorState End

	// FAssetEditorToolkit Begin
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FName GetToolkitFName() const override { return "MyCustomAssetEditor3"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("My Custom Asset Editor3"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "My Custom Asset Editor3"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
	// FAssetEditorToolkit End

private:
	void SyncGraphToAsset();
	void SyncAssetToGraph();
	
	UMyCustomAsset3* Asset = nullptr;
	UEdGraph* Graph = nullptr;
};
