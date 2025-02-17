#include "EditorHelper.h"
#include "AssetManagerEditorModule.h"

UObject *UEditorHelper::GetActiveEditAsset()
{
    if (!GEditor)
    {
        UE_LOG(LogTemp, Warning, TEXT("GEditor is null"));
        return nullptr;
    }

    UAssetEditorSubsystem *AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
    if (!AssetEditorSubsystem)
    {
        return nullptr;
    }

    TArray<UObject *> EditedAssets = AssetEditorSubsystem->GetAllEditedAssets();
    for (UObject *Asset : EditedAssets)
    {
        IAssetEditorInstance *Editor = AssetEditorSubsystem->FindEditorForAsset(Asset, false);
        if (!Editor)
            continue;

        TSharedPtr<class FTabManager> TabManager = Editor->GetAssociatedTabManager();
        if (!TabManager.IsValid())
            continue;

        TSharedPtr<SDockTab> Tab = TabManager->GetOwnerTab();
        if (!Tab.IsValid())
            continue;

        TSharedPtr<SWindow> Window = Tab->GetParentWindow();
        if (!Window.IsValid())
            continue;

        if (Tab->IsForeground() && Window->IsActive())
        {
            return Asset;
        }
    }

    return nullptr;
}

bool UEditorHelper::CloseActiveEditAsset()
{
    if (!GEditor)
    {
        UE_LOG(LogTemp, Warning, TEXT("GEditor is null"));
        return false;
    }

    UAssetEditorSubsystem *AssetEditorSubsystem = GEditor->GetEditorSubsystem<UAssetEditorSubsystem>();
    if (!AssetEditorSubsystem)
    {
        return false;
    }

    TArray<UObject *> EditedAssets = AssetEditorSubsystem->GetAllEditedAssets();
    for (UObject *Asset : EditedAssets)
    {
        IAssetEditorInstance *Editor = AssetEditorSubsystem->FindEditorForAsset(Asset, false);
        if (!Editor)
            continue;

        TSharedPtr<class FTabManager> TabManager = Editor->GetAssociatedTabManager();
        if (!TabManager.IsValid())
            continue;

        TSharedPtr<SDockTab> Tab = TabManager->GetOwnerTab();
        if (!Tab.IsValid())
            continue;

        TSharedPtr<SWindow> Window = Tab->GetParentWindow();
        if (!Window.IsValid())
            continue;

        if (Tab->IsForeground() && Window->IsActive())
        {
            Editor->CloseWindow(EAssetEditorCloseReason::AssetEditorHostClosed);
            return true;
        }
    }

    return false;
}

bool UEditorHelper::ShowActiveEditAssetReference()
{
    UObject *FocusedAsset = GetActiveEditAsset();
    if (!FocusedAsset)
    {
        return false;
    }

    const UPackage *Package = FocusedAsset->GetOutermost();
    if (!Package)
    {
        return false;
    }

    IAssetManagerEditorModule &AssetManagerEditorModule = IAssetManagerEditorModule::Get();
    AssetManagerEditorModule.OpenReferenceViewerUI({FAssetIdentifier(Package->GetFName())});

    return true;
}