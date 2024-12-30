#include "SMyCustomAsset3EditorWindow.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Editor.h"
#include "MyCustomAsset3.h"
#include "MyCustomAsset3EditorState.h"

#define LOCTEXT_NAMESPACE "SMyCustomAsset3EditorWindow"

void SMyCustomAsset3EditorWindow::Construct(const FArguments& InArgs, IMyCustomAsset3EditorState *InState)
{
    State = InState;

    ChildSlot
    [
        SNew(SVerticalBox)
          + SVerticalBox::Slot()
        .FillHeight(1.0f)
        .HAlign(HAlign_Fill)
        [
            SNew(SGraphEditor)
                .IsEditable(true)
                .GraphToEdit(State->GetGraph())
        ]
    ];

    FCoreUObjectDelegates::OnObjectPropertyChanged.AddSP(SharedThis(this), &SMyCustomAsset3EditorWindow::OnObjectPropertyChanged);
}

SMyCustomAsset3EditorWindow::~SMyCustomAsset3EditorWindow()
{
    FCoreUObjectDelegates::OnObjectPropertyChanged.RemoveAll(this);
}

TSharedRef<SDockTab> SMyCustomAsset3EditorWindow::OnSpawnTab(const FSpawnTabArgs& SpawnTabArgs)
{
    return SNew(SDockTab)
        .TabRole(NomadTab)
        [
            SNew(SMyCustomAsset3EditorWindow, State)
        ];
}

void SMyCustomAsset3EditorWindow::OnObjectPropertyChanged(UObject* Object, FPropertyChangedEvent& PropertyChangedEvent)
{
    if (Object == State->GetAsset())
    {
        this->Invalidate(EInvalidateWidgetReason::None);
    }
}

#undef LOCTEXT_NAMESPACE
