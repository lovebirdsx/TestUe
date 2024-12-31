#pragma once

class MYASSETEDITOR_API FResourceManager
{
public:
	static const FName StyleSetName;
	static const FName ClassThumbnail_MyCustomAsset2;
	static const FName ClassIcon_MyCustomAsset2;
	static const FName ClassThumbnail_MyCustomAsset3;
	static const FName ClassIcon_MyCustomAsset3;
	static const FName CustomAsset3Editor_AddNode;
	static const FName CustomAsset3Editor_DeleteNode;
	static const FName CustomAsset3Editor_AddNodePin;
	static const FName CustomAsset3Editor_DeleteNodePin;

	void RegisterResource();
	void UnregisterResource();

private:
	TSharedPtr<FSlateStyleSet> StyleSet = nullptr;
};
