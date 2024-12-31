#pragma once

class UCustomRuntimeGraph;

class FCustomGraphOperations
{
public:
	static void RuntimeGraphToUIGraph(const UCustomRuntimeGraph* InRuntimeGraph, UEdGraph* InUIGraph);
	static void UIGraphToRuntimeGraph(const UEdGraph* InUIGraph, UCustomRuntimeGraph* InRuntimeGraph);
};
