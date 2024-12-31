#include "CustomEditor3/SMyCustomAsset3EditorWindow.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Widgets/Input/SButton.h"
#include "Editor.h"
#include "CustomEditor3/MyCustomAsset3EditorState.h"

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

}

#undef LOCTEXT_NAMESPACE
