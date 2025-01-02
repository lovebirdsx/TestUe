#pragma once

#include "CoreMinimal.h"
#include "MyCustomAsset3EditorState3.h"
#include "Toolkits/AssetEditorToolkit.h"

class UMyCustomAsset3;

class FMyCustomAsset3EditorToolkit : public FAssetEditorToolkit, public IMyCustomAsset3EditorState3, public FEditorUndoClient
{
public:
	virtual ~FMyCustomAsset3EditorToolkit() override;
	
	void InitEditor(const FAssetOpenArgs& OpenArgs);	

	// IMyCustomAsset3EditorState3 Begin
	virtual UMyCustomAsset3* GetAsset() override { return Asset; }
	virtual UEdGraph* GetGraph() override { return Graph; }
	// IMyCustomAsset3EditorState3 End

	// FAssetEditorToolkit Begin
	virtual void RegisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;
	virtual void UnregisterTabSpawners(const TSharedRef<FTabManager>& TabManager) override;

	virtual FName GetToolkitFName() const override { return "MyCustomAssetEditor3"; }
	virtual FText GetBaseToolkitName() const override { return INVTEXT("My Custom Asset Editor3"); }
	virtual FString GetWorldCentricTabPrefix() const override { return "My Custom Asset Editor3"; }
	virtual FLinearColor GetWorldCentricTabColorScale() const override { return {}; }
	virtual void OnClose() override;
	// FAssetEditorToolkit End

	// FEditorUndoClient Begin
	virtual bool MatchesContext(const FTransactionContext& InContext, const TArray<TPair<UObject*, FTransactionObjectEvent>>& TransactionObjectContexts) const override;
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	// FEditorUndoClient End

private:
	void SyncGraphToAsset();
	void SyncAssetToGraph();
	
	UMyCustomAsset3* Asset = nullptr;
	UEdGraph* Graph = nullptr;
};
