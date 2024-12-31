#include "CustomEditor2/AssetDefinition_MyCustomAsset2.h"

#include "MyCustomAsset2.h"
#include "CustomEditor2/MyCustomAsset2EditorToolkit.h"

#define LOCTEXT_NAMESPACE "MyCustomAssetEditor"

FText UAssetDefinition_MyCustomAsset2::GetAssetDisplayName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset2", "My Custom Asset 2");
}

FText UAssetDefinition_MyCustomAsset2::GetAssetDescription(const FAssetData& AssetData) const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_MyCustomAsset_Desc 2", "My Custom Asset Description 2");
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