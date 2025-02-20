#include "EditorHelperInputProcessor.h"
#include "Selection.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "EditorHelper.h"

namespace
{
    bool TryFocusOnActiveEditAsset()
    {
        UObject *FocusedAsset = UEditorHelper::GetActiveEditAsset();
        if (!FocusedAsset)
        {
            return false;
        }

        FContentBrowserModule &ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
        ContentBrowserModule.Get().SyncBrowserToAssets({FAssetData(FocusedAsset)});
        return true;
    }
}

void FEditorHelperInputProcessor::Tick(const float DeltaTime, FSlateApplication &SlateApp, TSharedRef<ICursor> Cursor)
{
}

bool FEditorHelperInputProcessor::HandleKeyDownEvent(FSlateApplication &SlateApp, const FKeyEvent &InKeyEvent)
{
    FKey Key = InKeyEvent.GetKey();
    bool bControlDown = InKeyEvent.IsControlDown();
    bool bShiftDown = InKeyEvent.IsShiftDown();
    bool bAltDown = InKeyEvent.IsAltDown();
    
    if (Key == EKeys::B && bControlDown && !bShiftDown && !bAltDown)
    {
        if (TryFocusOnActiveEditAsset())
        {
            return true;
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Failed to focus on selected asset"));
        }
    }
    else if (Key == EKeys::W && bControlDown && !bShiftDown && !bAltDown)
    {
        if (UEditorHelper::CloseActiveEditAsset())
        {
            return true;
        }
    }
    else if (Key == EKeys::R && bAltDown && bShiftDown && !bControlDown)
    {
        if (UEditorHelper::ShowActiveEditAssetReference())
        {
            return true;
        }
    }
    else if (Key == EKeys::G && bControlDown && bAltDown && !bShiftDown)
    {
        if (UEditorHelper::OpenGameplayTagManager())
        {
            return true;
        }
    }
    return false;
}
