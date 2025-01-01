#include "ResouceManager.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

const FName FResourceManager::StyleSetName(TEXT("CustomAssetEditorStyle3"));
const FName FResourceManager::ClassThumbnail_MyCustomAsset2(TEXT("ClassThumbnail.MyCustomAsset2"));
const FName FResourceManager::ClassIcon_MyCustomAsset2(TEXT("ClassIcon.MyCustomAsset2"));
const FName FResourceManager::ClassThumbnail_MyCustomAsset3(TEXT("ClassThumbnail.MyCustomAsset3"));
const FName FResourceManager::ClassIcon_MyCustomAsset3(TEXT("ClassIcon.MyCustomAsset3"));
const FName FResourceManager::CustomAsset3Editor_AddNode(TEXT("CustomAsset3Editor.AddNode"));
const FName FResourceManager::CustomAsset3Editor_DeleteNode(TEXT("CustomAsset3Editor.DeleteNode"));
const FName FResourceManager::CustomAsset3Editor_AddNodePin(TEXT("CustomAsset3Editor.AddNodePin"));
const FName FResourceManager::CustomAsset3Editor_DeleteNodePin(TEXT("CustomAsset3Editor.DeleteNodePin"));

void FResourceManager::RegisterResource()
{
	StyleSet = MakeShareable(new FSlateStyleSet(StyleSetName));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("MyAsset")->GetBaseDir() / TEXT("Resources"));

	FSlateImageBrush *ThumbnailBrush2 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("PinkStar"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *IconBrush2 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("YellowStar"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *ThumbnailBrush3 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("BlueStar"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *IconBrush3 = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("GrayStar"), TEXT(".png")), FVector2D(128, 128));

	FSlateImageBrush *AddNodeBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("PinkStar"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *DeleteNodeBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("YellowStar"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *AddNodePinBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("BlueStar"), TEXT(".png")), FVector2D(128, 128));
	FSlateImageBrush *DeleteNodePinBrush = new FSlateImageBrush(StyleSet->RootToContentDir(TEXT("GrayStar"), TEXT(".png")), FVector2D(128, 128));
	
	StyleSet->Set(ClassThumbnail_MyCustomAsset2, ThumbnailBrush2);
	StyleSet->Set(ClassIcon_MyCustomAsset2, IconBrush2);
	StyleSet->Set(ClassThumbnail_MyCustomAsset3, ThumbnailBrush3);
	StyleSet->Set(ClassIcon_MyCustomAsset3, IconBrush3);
	StyleSet->Set(CustomAsset3Editor_AddNode, AddNodeBrush);
	StyleSet->Set(CustomAsset3Editor_DeleteNode, DeleteNodeBrush);
	StyleSet->Set(CustomAsset3Editor_AddNodePin, AddNodePinBrush);
	StyleSet->Set(CustomAsset3Editor_DeleteNodePin, DeleteNodePinBrush);	

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FResourceManager::UnregisterResource()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
}
