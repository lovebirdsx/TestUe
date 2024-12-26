#pragma once

#include "CoreMinimal.h"
#include "BlueprintEditor.h"

class UMyBlueprint;

class MYBLUEPRINT_API FMyBlueprintEditor : public FBlueprintEditor
{
public:
	virtual void InitMyBlueprintEditor(::EToolkitMode::Type Mode, const TSharedPtr<IToolkitHost>& InitToolkitHost, UBlueprint* Blueprint);
};
