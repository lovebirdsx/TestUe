#include "MyCustomAsset2.h"
#include "MyCustomAsset2EditorToolkit.h"
#include "SMyCustomAsset2EditorWindow.h"

#define LAYOUT "MyCustomAsset2EditorLayout"
#define EDITOR_TAB "MyCustomAsset2EditorTab"
#define DETAILS_TAB "MyCustomAsset2DetailsTab"

void FMyCustomAsset2EditorToolkit::InitEditor(const FAssetOpenArgs& OpenArgs)
{
	const TArray<UMyCustomAsset2*>& InObjects = OpenArgs.LoadObjects<UMyCustomAsset2>();
	if (InObjects.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No asset(type is UMyCustomAsset2) to edit"));
		return;
	}
	
	Asset = InObjects[0];

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(LAYOUT)
	->AddArea
	(
		FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
		->Split
		(
			FTabManager::NewSplitter()
			->SetSizeCoefficient(0.6f)
			->SetOrientation(Orient_Horizontal)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.8f)
				->AddTab(EDITOR_TAB, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.2f)
				->AddTab(DETAILS_TAB, ETabState::OpenedTab)
			)
		)
		->Split
		(
			FTabManager::NewStack()
			->SetSizeCoefficient(0.4f)
			->AddTab("OutputLog", ETabState::OpenedTab)
		)
	);

	const TArray<UObject*> InObjectsArray = { Asset };
	InitAssetEditor(EToolkitMode::Standalone, OpenArgs.ToolkitHost, FName("MyCustomAsset2Editor"), Layout, true, true, InObjectsArray);
}

void FMyCustomAsset2EditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Normal Distribution Editor"));

	InTabManager->RegisterTabSpawner(EDITOR_TAB, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			SNew(SMyCustomAsset2EditorWindow, this->Asset)
		];
	}))
	.SetDisplayName(INVTEXT("Editor"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	FDetailsViewArgs DetailsViewArgs;
	DetailsViewArgs.NameAreaSettings = FDetailsViewArgs::HideNameArea;
	const TSharedRef<IDetailsView> DetailsView = PropertyEditorModule.CreateDetailView(DetailsViewArgs);
	DetailsView->SetObjects(TArray<UObject*>{ Asset });
	InTabManager->RegisterTabSpawner(DETAILS_TAB, FOnSpawnTab::CreateLambda([=](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			DetailsView
		];
	}))
	.SetDisplayName(INVTEXT("Details"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FMyCustomAsset2EditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(EDITOR_TAB);
	InTabManager->UnregisterTabSpawner(DETAILS_TAB);
}
