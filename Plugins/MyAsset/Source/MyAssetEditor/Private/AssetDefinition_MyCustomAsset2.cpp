#include "AssetDefinition_MyCustomAsset2.h"

#include "MyCustomAsset2.h"
#include "MyCustomAsset2EditorToolkit.h"

#define LOCTEXT_NAMESPACE "MyCustomAssetEditor"

FText UAssetDefinition_MyCustomAsset2::GetAssetDisplayName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset", "My Custom Asset");
}

FText UAssetDefinition_MyCustomAsset2::GetAssetDescription(const FAssetData& AssetData) const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset_Desc", "My Custom Asset Description");
}

FLinearColor UAssetDefinition_MyCustomAsset2::GetAssetColor() const
{
	return FLinearColor(FColor(255, 100, 100));
}

TSoftClassPtr<> UAssetDefinition_MyCustomAsset2::GetAssetClass() const
{
	return UMyCustomAsset2::StaticClass();
}

TConstArrayView<FAssetCategoryPath> UAssetDefinition_MyCustomAsset2::GetAssetCategories() const
{
	static const auto Categories = { EAssetCategoryPaths::Misc };
	return Categories;
}

EAssetCommandResult UAssetDefinition_MyCustomAsset2::OpenAssets(const FAssetOpenArgs& OpenArgs) const
{
	MakeShared<FMyCustomAsset2EditorToolkit>()->InitEditor(OpenArgs);

	return EAssetCommandResult::Handled;
}

UThumbnailInfo* UAssetDefinition_MyCustomAsset2::LoadThumbnailInfo(const FAssetData& InAssetData) const
{
	return Super::LoadThumbnailInfo(InAssetData);
}

#undef LOCTEXT_NAMESPACE