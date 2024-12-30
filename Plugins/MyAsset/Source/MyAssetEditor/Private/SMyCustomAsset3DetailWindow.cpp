#include "SMyCustomAsset3DetailWindow.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Widgets/Input/SNumericEntryBox.h"
#include "Editor.h"
#include "MyCustomAsset3.h"

#define LOCTEXT_NAMESPACE "SMyCustomAsset3DetailWindow"

void SMyCustomAsset3DetailWindow::Construct(const FArguments& InArgs, UMyCustomAsset3* InAsset)
{
    Asset = InAsset;

    ChildSlot
    [
        SNew(SBox)
        .Padding(10)
        .WidthOverride(400)
        .HeightOverride(200)
        [
            SNew(SVerticalBox)
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(5)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("AssetNameLabel", "Asset Name:"))
            ]
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(5)
            [
                SAssignNew(AssetNameBox, SEditableTextBox)
                .Text_Lambda([this]()
                {
                    return FText::FromString(Asset->AssetName);
                })
                .OnVerifyTextChanged(this, &SMyCustomAsset3DetailWindow::OnAssetNameChanged)
            ]
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(5)
            [
                SNew(STextBlock)
                .Text(LOCTEXT("AssetValueLabel", "Asset Value:"))
            ]
            
            + SVerticalBox::Slot()
            .AutoHeight()
            .Padding(5)
            [
                SAssignNew(AssetValueBox, SNumericEntryBox<int32>)
                .Value_Lambda([this]()
                {                    
                    return TOptional(Asset ? Asset->AssetValue : 0);
                })
                .OnValueCommitted(this, &SMyCustomAsset3DetailWindow::OnAssetValueCommitted)
            ]           
        ]
    ];

    FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(SharedThis(this), &SMyCustomAsset3DetailWindow::OnObjectPropertyChanged);
}

SMyCustomAsset3DetailWindow::~SMyCustomAsset3DetailWindow()
{
    FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}

TSharedRef<SDockTab> SMyCustomAsset3DetailWindow::OnSpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(ETabRole::NomadTab)
        [
            SNew(SMyCustomAsset3DetailWindow, Asset)
        ];
}

void SMyCustomAsset3DetailWindow::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
    if (Object == Asset)
    {
        this->Invalidate(EInvalidateWidgetReason::None);
    }
}

void SMyCustomAsset3DetailWindow::OnAssetValueCommitted(const int Value, ETextCommit::Type CommitType)
{
    if (!Asset)
    {
        return;
    }

    const FScopedTransaction Transaction(LOCTEXT("ChangeAssetValue", "Change Asset Value"));
    Asset->Modify();
    Asset->AssetValue = Value;
    Asset->PostEditChange();
}

bool SMyCustomAsset3DetailWindow::OnAssetNameChanged(const FText& Text, FText& Text1)
{
    if (!Asset)
    {
        return false;
    }

    const FScopedTransaction Transaction(LOCTEXT("ChangeAssetName", "Change Asset Name"));
    Asset->Modify();
    Asset->AssetName = Text.ToString();
    Asset->PostEditChange();

    return true;
}

#undef LOCTEXT_NAMESPACE
