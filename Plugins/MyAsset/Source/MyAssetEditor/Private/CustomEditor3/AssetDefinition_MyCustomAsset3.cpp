#include "CustomEditor3/AssetDefinition_MyCustomAsset3.h"

#include "MyCustomAsset3.h"
#include "CustomEditor3/MyCustomAsset3EditorToolkit.h"
#include "Styling/SlateIconFinder.h"

#define LOCTEXT_NAMESPACE "MyCustomAssetEditor"

FText UAssetDefinition_MyCustomAsset3::GetAssetDisplayName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset3", "My Custom Asset 3");
}

FText UAssetDefinition_MyCustomAsset3::GetAssetDescription(const FAssetData& AssetData) const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset_Desc 3", "My Custom Asset Description 3");
}

FLinearColor UAssetDefinition_MyCustomAsset3::GetAssetColor() const
{
	return FLinearColor(FColor(100, 255, 100));
}

TSoftClassPtr<> UAssetDefinition_MyCustomAsset3::GetAssetClass() const
{
	return UMyCustomAsset3::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_MyCustomAsset3::GetAssetCategories() const
{
	static const auto Categories = { EAssetCategoryPaths::Misc };
	return Categories;
}

EAssetCommandResult UAssetDefinition_MyCustomAsset3::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	MakeShared<FMyCustomAsset3EditorToolkit>()->InitEditor(OpenArgs);

	return EAssetCommandResult::Handled;
}

UThumbnailInfo* UAssetDefinition_MyCustomAsset3::LoadThumbnailInfo(const FAssetData& InAssetData) const
{
	return Super::LoadThumbnailInfo(InAssetData);
}

#undef LOCTEXT_NAMESPACE