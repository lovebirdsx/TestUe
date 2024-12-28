#include "FAssetTypeActions_MyBlueprint.h"
#include "MyBlueprint.h"
#include "MyBlueprintEditor.h"
#include "MyBlueprintFactory.h"
#include "MyBpParent.h"

UClass* FAssetTypeActions_MyBlueprint::GetSupportedClass() const
{
	return UMyBlueprint::StaticClass();
}

FText FAssetTypeActions_MyBlueprint::GetName() const
{
	return NSLOCTEXT("AssetTypeActions_MyBlueprint", "MyBlueprintAssetTypeActions", "My Blueprint");
}

FColor FAssetTypeActions_MyBlueprint::GetTypeColor() const
{
	return FColor(0, 200, 255);
}

uint32 FAssetTypeActions_MyBlueprint::GetCategories()
{
	return EAssetTypeCategories::Blueprint;
}

void FAssetTypeActions_MyBlueprint::OpenAssetEditor(const TArray<UObject*>& InObjects, const TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	for (UObject *Object : InObjects)
	{
		if (UMyBlueprint *Blueprint = Cast<UMyBlueprint>(Object))
		{
			const TSharedRef<FMyBlueprintEditor> NewEditor(new FMyBlueprintEditor());
			NewEditor->InitMyBlueprintEditor(EToolkitMode::Standalone, EditWithinLevelEditor, Blueprint);
		}
	}	
}

void FAssetTypeActions_MyBlueprint::OpenAssetEditor(const TArray<UObject*>& InObjects,
	const EAssetTypeActivationOpenedMethod OpenedMethod, const TSharedPtr<IToolkitHost> EditWithinLevelEditor)
{
	if (OpenedMethod == EAssetTypeActivationOpenedMethod::Edit)
	{
		OpenAssetEditor(InObjects, EditWithinLevelEditor);
	}
}

UFactory* FAssetTypeActions_MyBlueprint::GetFactoryForBlueprintType(UBlueprint* InBlueprint) const
{
	UMyBlueprintFactory *MyFactory = NewObject<UMyBlueprintFactory>();
	MyFactory->ParentClass = UMyBpParent::StaticClass();
	return MyFactory;
}
