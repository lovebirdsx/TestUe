// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCustomAssetDetails.h"

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"
#include "MyCustomAsset.h"

void FMyCustomAssetDetails::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	TArray<TWeakObjectPtr<>> Objects;
	DetailBuilder.GetObjectsBeingCustomized(Objects);

	if (Objects.Num() > 1 || Objects.Num() == 0)
		return;

	const UMyCustomAsset* MyCustomAsset = Cast<UMyCustomAsset>(Objects[0].Get());
	if (MyCustomAsset == nullptr)
		return;

	const TSharedRef<IPropertyHandle> AssetNameHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMyCustomAsset, AssetName), UMyCustomAsset::StaticClass());
	const TSharedRef<IPropertyHandle> AssetValueHandle = DetailBuilder.GetProperty(GET_MEMBER_NAME_CHECKED(UMyCustomAsset, AssetValue), UMyCustomAsset::StaticClass());

	DetailBuilder.HideProperty(AssetNameHandle);
	DetailBuilder.HideProperty(AssetValueHandle);

	IDetailCategoryBuilder& CustomCategory = DetailBuilder.EditCategory("MyCustom");

	CustomCategory.AddCustomRow(FText::FromString(TEXT("Custom Asset")))
	[
		SNew(STextBlock).Text(FText::FromString(TEXT("This is show by custom details")))
	];
	
	CustomCategory.AddCustomRow(AssetNameHandle->GetPropertyDisplayName())
	.NameContent()
	[
		AssetNameHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		AssetNameHandle->CreatePropertyValueWidget()
	];

	CustomCategory.AddCustomRow(AssetValueHandle->GetPropertyDisplayName())
	.NameContent()
	[
		AssetValueHandle->CreatePropertyNameWidget()
	]
	.ValueContent()
	[
		AssetValueHandle->CreatePropertyValueWidget()
	];
}

TSharedRef<IDetailCustomization> FMyCustomAssetDetails::MakeInstance()
{
	return MakeShareable(new FMyCustomAssetDetails);
}
