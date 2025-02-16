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
    if (InKeyEvent.GetKey() == EKeys::B && InKeyEvent.IsControlDown())
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
    return false;
}
