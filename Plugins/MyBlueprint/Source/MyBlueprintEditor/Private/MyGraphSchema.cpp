// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGraphSchema.h"

#include "Nodes/MyK2Node_Custom.h"

void UMyGraphSchema::GetGraphContextActions(FGraphContextMenuBuilder& ContextMenuBuilder) const
{
	const TSharedPtr<FEdGraphSchemaAction_NewNode> NewNodeAction(new FEdGraphSchemaAction_NewNode(
		FText::FromString(TEXT("Custom Nodes")),
		FText::FromString(TEXT("Add My Custom Node")),
		FText::FromString(TEXT("Insert a custom node into the graph")),
		0
	));

	NewNodeAction->NodeTemplate = NewObject<UMyK2Node_Custom>(ContextMenuBuilder.OwnerOfTemporaries);
	ContextMenuBuilder.AddAction(NewNodeAction);
}

void UMyGraphSchema::GetContextMenuActions(class UToolMenu* Menu, class UGraphNodeContextMenuContext* Context) const
{
	FToolMenuSection& Section = Menu->AddSection("MySection", NSLOCTEXT("MySection", "My Section", "My Section"));

	Section.AddMenuEntry("MyMenuEntry",
		NSLOCTEXT("MyMenuEntry", "My Menu Entry", "My Menu Entry"),
		NSLOCTEXT("MyMenuEntryTooltip", "My Menu Entry Tooltip", "My Menu Entry Tooltip"),
		FSlateIcon(),
		FUIAction(
			FExecuteAction::CreateLambda(
				[]()
				{
					FPlatformMisc::MessageBoxExt(EAppMsgType::Ok, TEXT("My Menu Entry Clicked"), TEXT("My Menu Entry"));
				}
			)
		)
	);
}
