﻿#include "CustomEditor3/MyCustomAsset3EditorToolkit.h"

#include "CustomRuntimeGraph3.h"
#include "CustomEditor3/CustomGraphSchema3.h"
#include "MyCustomAsset3.h"
#include "CustomEditor3/CustomGraphOperations3.h"
#include "CustomEditor3/SMyCustomAsset3DetailWindow.h"
#include "CustomEditor3/SMyCustomAsset3EditorWindow.h"
#include "Kismet2/BlueprintEditorUtils.h"

#define MY_CUSTOM_ASSET3_LAYOUT "MyCustomAsset3EditorLayout"
#define MY_CUSTOM_ASSET3_EDITOR_TAB "MyCustomAsset3EditorTab"
#define MY_CUSTOM_ASSET3_DETAILS_TAB "MyCustomAsset3DetailsTab"

void FMyCustomAsset3EditorToolkit::InitEditor(const FAssetOpenArgs& OpenArgs)
{
	const TArray<UMyCustomAsset3*>& InObjects = OpenArgs.LoadObjects<UMyCustomAsset3>();
	if (InObjects.Num() <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("No asset(type is UMyCustomAsset3) to edit"));
		return;
	}
	
	Asset = InObjects[0];
	Graph = FBlueprintEditorUtils::CreateNewGraph(
		Asset,
		NAME_None,
		UEdGraph::StaticClass(),
		UCustomGraphSchema3::StaticClass()
	);

	SyncAssetToGraph();
	Graph->AddOnGraphChangedHandler(FOnGraphChanged::FDelegate::CreateLambda(
		[this] (const FEdGraphEditAction& Action)
		{
			this->SyncGraphToAsset();
		}		
	));

	const TSharedRef<FTabManager::FLayout> Layout = FTabManager::NewLayout(MY_CUSTOM_ASSET3_LAYOUT)
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
				->SetSizeCoefficient(0.7f)
				->AddTab(MY_CUSTOM_ASSET3_EDITOR_TAB, ETabState::OpenedTab)
			)
			->Split
			(
				FTabManager::NewStack()
				->SetSizeCoefficient(0.3f)
				->AddTab(MY_CUSTOM_ASSET3_DETAILS_TAB, ETabState::OpenedTab)
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
	InitAssetEditor(EToolkitMode::Standalone, OpenArgs.ToolkitHost, FName("MyCustomAsset3Editor"), Layout, true, true, InObjectsArray);
}

void FMyCustomAsset3EditorToolkit::RegisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::RegisterTabSpawners(InTabManager);

	WorkspaceMenuCategory = InTabManager->AddLocalWorkspaceMenuCategory(INVTEXT("Normal Distribution Editor"));

	InTabManager->RegisterTabSpawner(MY_CUSTOM_ASSET3_EDITOR_TAB, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			SNew(SMyCustomAsset3EditorWindow, this)
		];
	}))
	.SetDisplayName(INVTEXT("Editor"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());

	
	InTabManager->RegisterTabSpawner(MY_CUSTOM_ASSET3_DETAILS_TAB, FOnSpawnTab::CreateLambda([this](const FSpawnTabArgs&)
	{
		return SNew(SDockTab)
		[
			SNew(SMyCustomAsset3DetailWindow, this->Asset)
		];
	}))
	.SetDisplayName(INVTEXT("Details"))
	.SetGroup(WorkspaceMenuCategory.ToSharedRef());
}

void FMyCustomAsset3EditorToolkit::UnregisterTabSpawners(const TSharedRef<FTabManager>& InTabManager)
{
	FAssetEditorToolkit::UnregisterTabSpawners(InTabManager);
	InTabManager->UnregisterTabSpawner(MY_CUSTOM_ASSET3_EDITOR_TAB);
	InTabManager->UnregisterTabSpawner(MY_CUSTOM_ASSET3_DETAILS_TAB);
}

void FMyCustomAsset3EditorToolkit::OnClose()
{
	SyncGraphToAsset();
}

void FMyCustomAsset3EditorToolkit::SyncGraphToAsset()
{
	if (Asset == nullptr || Graph == nullptr)
	{
		return;
	}

	if (Asset->RuntimeGraph == nullptr)
	{
		Asset->RuntimeGraph = NewObject<UCustomRuntimeGraph3>();
	}
	
	FCustomGraphOperations3::UIGraphToRuntimeGraph(Graph, Asset->RuntimeGraph);	
}

void FMyCustomAsset3EditorToolkit::SyncAssetToGraph()
{
	if (Asset->RuntimeGraph == nullptr || Graph == nullptr)
	{
		return;
	}

	FCustomGraphOperations3::RuntimeGraphToUIGraph(Asset->RuntimeGraph, Graph);	
}