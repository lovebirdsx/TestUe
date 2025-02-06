#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "TestUeSettings.generated.h"

/**
 * Test Ue Editor模块的设置
 */
UCLASS(config = Editor, defaultconfig, meta = (DisplayName = "Test Ue Settings"))
class TESTUEEDITOR_API UTestUeSettings : public UDeveloperSettings
{
    GENERATED_BODY()

public:
    UTestUeSettings();

    // 蓝图编译后是否运行测试
    UPROPERTY(EditAnywhere, config, Category = "Test Ue Settings", meta = (DisplayName = "Run Test After Blueprint Compile"))
    bool bRunTestAfterBpCompile;
};
