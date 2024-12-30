#pragma once

#include "Widgets/SCompoundWidget.h"
#include "MyCustomAsset2.h"

class SMyCustomAsset2EditorWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCustomAsset2EditorWindow) {}
	SLATE_ARGUMENT(UMyCustomAsset2*, Asset)
SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, UMyCustomAsset2* InAsset);
	virtual ~SMyCustomAsset2EditorWindow() override;

	TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& SpawnTabArgs);

private:
	void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);
	
	void OnAssetValueCommitted(int Value, ETextCommit::Type CommitType);
	bool OnAssetNameChanged(const FText& Text, FText& Text1);	
	
	UMyCustomAsset2* Asset = nullptr;

	// 编辑器控件
	TSharedPtr<SEditableTextBox> AssetNameBox;
	TSharedPtr<SNumericEntryBox<int32>> AssetValueBox;
};
