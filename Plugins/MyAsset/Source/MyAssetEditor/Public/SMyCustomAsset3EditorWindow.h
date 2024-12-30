#pragma once

#include "Widgets/SCompoundWidget.h"

class IMyCustomAsset3EditorState;
class UMyCustomAsset3;

class SMyCustomAsset3EditorWindow : public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SMyCustomAsset3EditorWindow) {}
	SLATE_ARGUMENT(UMyCustomAsset3*, State)
SLATE_END_ARGS()

	void Construct(const FArguments& InArgs, IMyCustomAsset3EditorState *InState);
	virtual ~SMyCustomAsset3EditorWindow() override;

	TSharedRef<SDockTab> OnSpawnTab(const FSpawnTabArgs& SpawnTabArgs);

private:
	void OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent);	
	
	IMyCustomAsset3EditorState *State = nullptr;

	// 编辑器控件
	TSharedPtr<SEditableTextBox> AssetNameBox;
	TSharedPtr<SNumericEntryBox<int32>> AssetValueBox;
};
