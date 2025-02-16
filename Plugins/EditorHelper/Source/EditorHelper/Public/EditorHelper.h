#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "EditorHelper.generated.h"

UCLASS()
class EDITORHELPER_API UEditorHelper : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    // 获得当前编辑的且激活（对应的Tab有焦点）的资源
    UFUNCTION(BlueprintCallable, Category = "EditorHelper")
    static UObject *GetActiveEditAsset();
};
