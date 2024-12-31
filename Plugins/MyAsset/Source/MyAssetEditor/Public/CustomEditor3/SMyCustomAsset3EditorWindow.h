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

private:	
	IMyCustomAsset3EditorState *State = nullptr;
};
