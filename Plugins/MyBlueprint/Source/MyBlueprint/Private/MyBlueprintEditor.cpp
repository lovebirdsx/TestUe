#include "MyBlueprintEditor.h"

#include "BlueprintEditorModes.h"
#include "BlueprintEditorTabs.h"
#include "MyGraphSchema.h"

void FMyBlueprintEditor::InitMyBlueprintEditor(const ::EToolkitMode::Type Mode,
                                               const TSharedPtr<IToolkitHost>& InitToolkitHost, UBlueprint* Blueprint)
{
	CreateDefaultCommands();

	TArray<UBlueprint*> Blueprints;
	Blueprints.Add(Blueprint);

	InitBlueprintEditor(
		Mode,
		InitToolkitHost,
		Blueprints,
		true
	);

	for (UEdGraph *Graph : Blueprint->UbergraphPages)
	{
		Graph->Schema = UMyGraphSchema::StaticClass();
	}
}

