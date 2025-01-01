#pragma once

class UCustomRuntimeGraph3;

class FCustomGraphOperations3
{
public:
	static void RuntimeGraphToUIGraph(const UCustomRuntimeGraph3* InRuntimeGraph, UEdGraph* InUIGraph);
	static void UIGraphToRuntimeGraph(const UEdGraph* InUIGraph, UCustomRuntimeGraph3* InRuntimeGraph);
};
