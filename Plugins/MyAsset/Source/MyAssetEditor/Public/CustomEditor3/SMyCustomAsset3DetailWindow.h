#pragma once

#include "Widgets/SCompoundWidget.h"

class UMyCustomAsset3;

class SMyCustomAsset3DetailWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCustomAsset3DetailWindow) {}
	SLATE_ARGUMENT(UMyCustomAsset3*, Asset)
SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UMyCustomAsset3* InAsset);
	virtual ~SMyCustomAsset3DetailWindow() override;

	TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& SpawnTabArgs);

private:
	void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
	
	void OnAssetValueCommitted(int Value, ETextCommit::Type CommitType);
	bool OnAssetNameChanged(const FText& Text, FText& Text1);	
	
	UMyCustomAsset3* Asset = nullptr;

	// 编辑器控件
	TSharedPtr<SEditableTextBox> AssetNameBox;
	TSharedPtr<SNumericEntryBox<int32>> AssetValueBox;
};
