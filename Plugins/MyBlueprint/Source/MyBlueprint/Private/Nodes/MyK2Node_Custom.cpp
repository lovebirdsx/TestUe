// Fill out your copyright notice in the Description page of Project Settings.


#include "Nodes/MyK2Node_Custom.h"

FText UMyK2Node_Custom::GetNodeTitle(ENodeTitleType::Type TitleType) const
{
	return FText::FromString(TEXT("My Custom Node"));
}

void UMyK2Node_Custom::AllocateDefaultPins()
{
	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, FName(), nullptr, TEXT("In"));
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, FName(), nullptr, TEXT("Out"));
}

FText UMyK2Node_Custom::GetMenuCategory() const
{
	return FText::FromString(TEXT("Custom"));
}

void UMyK2Node_Custom::ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);
}
